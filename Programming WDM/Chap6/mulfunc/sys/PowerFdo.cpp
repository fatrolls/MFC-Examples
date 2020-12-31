// Power request handler notify driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

NTSTATUS DefaultPowerHandler(PDEVICE_EXTENSION pdx, IN PIRP Irp);

enum POWSTATE {
	InitialState = 0,				// initial state of FSM
	SysPowerUpPending,				// system power-up IRP forwarded
	SubPowerUpPending,				// waiting for nested device power up to finish
	SubPowerDownPending,			// waiting from device to power down before forwarding system power-down IRP
	SysPowerDownPending,			// waiting for system power-down IRP to finish
	DevPowerUpPending,				// waiting for device power-up IRP
	DevPowerDownPending,			// waiting for device power-down IRP
	ContextSavePending,				// context save is underway
	ContextRestorePending,			// context restore is underway
	DevQueryUpPending,				// device query for power-up pending
	DevQueryDownPending,			// device query for power-down pending
	QueueStallPending,				// waiting for device to be idle
	FinalState,						// final state of FSM
	NUMPOWSTATES,
	};

enum POWEVENT {
	NewIrp = 0,						// new query/set IRP
	MainIrpComplete,				// the main IRP has finished
	AsyncNotify,					// some other event has occurred
	NUMPOWEVENTS,
	};

typedef struct _POWCONTEXT {
	PDEVICE_EXTENSION pdx;			// our own device extension
	PIRP irp;						// the IRP we're processing
	enum POWSTATE state;			// current state of FSM
	NTSTATUS status;				// completion status for main IRP
	PKEVENT pev;					// event to set when IRP is complete
	DEVICE_POWER_STATE devstate;	// device power state to use
	DEVICE_POWER_STATE oldpower;	// previous device power state
	UCHAR MinorFunction;			// minor function to use in requested power IRP
	} POWCONTEXT, *PPOWCONTEXT;

NTSTATUS HandlePowerEvent(PPOWCONTEXT ctx, enum POWEVENT event);

#if DBG

	static char* fcnname[] = {
		"IRP_MN_WAIT_WAKE",
		"IRP_MN_POWER_SEQUENCE",
		"IRP_MN_SET_POWER",
		"IRP_MN_QUERY_POWER",
		};

	static char* sysstate[] = {
		"PowerSystemUnspecified",
		"PowerSystemWorking",
		"PowerSystemSleeping1",
		"PowerSystemSleeping2",
		"PowerSystemSleeping3",
		"PowerSystemHibernate",
		"PowerSystemShutdown",
		"PowerSystemMaximum",
		};

	static char* devstate[] = {
		"PowerDeviceUnspecified",
		"PowerDeviceD0",
		"PowerDeviceD1",
		"PowerDeviceD2",
		"PowerDeviceD3",
		"PowerDeviceMaximum",
		};
#endif // DBG
									  
///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchPowerFdo(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// DispatchPowerFdo
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_POWER);

	ULONG fcn = stack->MinorFunction;

	if (fcn == IRP_MN_SET_POWER || fcn == IRP_MN_QUERY_POWER)
		{						// handle set/query

#if DBG
		KdPrint((DRIVERNAME " - POWER Request (%s)", fcnname[fcn]));
		if (stack->Parameters.Power.Type == SystemPowerState)
			KdPrint((", S-state = %s\n", sysstate[stack->Parameters.Power.State.SystemState]));
		else
			KdPrint((", D-state = %s\n", devstate[stack->Parameters.Power.State.DeviceState]));
#endif // DBG
			{					// launch FSM
			PPOWCONTEXT ctx = (PPOWCONTEXT) ExAllocatePool(NonPagedPool, sizeof(POWCONTEXT));
			if (!ctx)
				{
				KdPrint((DRIVERNAME " - Can't allocate power context structure\n"));
				status = CompleteRequest(Irp, STATUS_INSUFFICIENT_RESOURCES);
				}
			else
				{				// process this IRP
				RtlZeroMemory(ctx, sizeof(POWCONTEXT));
				ctx->pdx = pdx;
				ctx->irp = Irp;
				status = HandlePowerEvent(ctx, NewIrp);
				}				// process this IRP
			}					// launch FSM
		}						// handle set/query

	else
		{						// handle other power request
		KdPrint((DRIVERNAME " - POWER Request (%s)\n", fcn < arraysize(fcnname) ? fcnname[fcn] : "??"));
			status = DefaultPowerHandler(pdx, Irp);
		}						// handle other power request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status;
	}							// DispatchPowerFdo

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NTSTATUS DefaultPowerHandler(PDEVICE_EXTENSION pdx, IN PIRP Irp)
	{							// DefaultPowerHandler
	PoStartNextPowerIrp(Irp);	// must be done while we own the IRP
	IoSkipCurrentIrpStackLocation(Irp);
	return PoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// DefaultPowerHandler

///////////////////////////////////////////////////////////////////////////////

VOID SendAsyncNotification(PVOID context)
	{							// SendAsyncNotification
	HandlePowerEvent((PPOWCONTEXT) context, AsyncNotify);
	}							// SendAsyncNotification

///////////////////////////////////////////////////////////////////////////////

struct SDSP_CONTEXT {
	PKEVENT pev;				// event to signal when request complete
	NTSTATUS status;			// ending status
	};

#pragma LOCKEDCODE

VOID SendDeviceSetPowerComplete(PDEVICE_OBJECT junk, UCHAR fcn, POWER_STATE state, SDSP_CONTEXT* context, PIO_STATUS_BLOCK pstatus)
	{							// SendDeviceSetPowerComplete
	context->status = pstatus->Status;
	KeSetEvent(context->pev, EVENT_INCREMENT, FALSE);
	}							// SendDeviceSetPowerComplete

NTSTATUS SendDeviceSetPower(PDEVICE_EXTENSION pdx, DEVICE_POWER_STATE devpower, BOOLEAN wait /* = FALSE */)
	{							// SendDeviceSetPower
	POWER_STATE state;
	state.DeviceState = devpower;
	NTSTATUS status;

	if (wait)
		{						// synchronous operation
		KEVENT event;
		KeInitializeEvent(&event, NotificationEvent, FALSE);
		SDSP_CONTEXT context = {&event};
		status = PoRequestPowerIrp(pdx->Pdo, IRP_MN_SET_POWER, state,
			(PREQUEST_POWER_COMPLETE) SendDeviceSetPowerComplete, &context, NULL);
		if (status == STATUS_PENDING)
			{
			KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
			status = context.status;
			}
		}						// synchronous operation
	else
		status = PoRequestPowerIrp(pdx->Pdo, IRP_MN_SET_POWER, state, NULL, NULL, NULL);
	
	return status;
	}							// SendDeviceSetPower

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NTSTATUS MainCompletionRoutine(PDEVICE_OBJECT junk, PIRP Irp, PPOWCONTEXT ctx);
VOID PoCompletionRoutine(PDEVICE_OBJECT junk, UCHAR fcn, POWER_STATE state, PPOWCONTEXT ctx, PIO_STATUS_BLOCK pstatus);
NTSTATUS SafePoCallDriver(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS HandlePowerEvent(PPOWCONTEXT ctx, enum POWEVENT event)
	{							// HandlePowerEvent
	NTSTATUS status = -1;		// an invalid value
	ASSERT(ctx);
	ASSERT((ULONG) event < NUMPOWEVENTS);

	PIRP Irp = ctx->irp;
	PIO_STACK_LOCATION stack = Irp ? IoGetCurrentIrpStackLocation(Irp) : NULL;

	PDEVICE_EXTENSION pdx = ctx->pdx;

	enum POWACTION {
		InvalidAction,			// code for invalid state/event combinations
		TriageNewIrp,			// decide what to do with new IRP
		QueueStallComplete,		// device queue has been stalled
		ForwardMainIrp,			// begin system or device IRP for more power
		SysPowerUpComplete,		// system power-up IRP completed
		SysPowerDownComplete,	// system power-down IRP completed
		SelectDState,			// choose D-state corresponding to main IRP's S-state
		SendDeviceIrp,			// send device IRP
		CompleteMainIrp,		// complete the main IRP
		DestroyContext,			// terminate FSM
		SubPowerUpComplete,		// nested power-up IRP finished or failed
		SubPowerDownComplete,	// nested power-down IRP finished or failed
		DevPowerUpComplete,		// device power-up IRP has completed
		SaveContext,			// save context in preparation for powering down
		ContextSaveComplete,	// device context has been saved
		ContextRestoreComplete,	// device context has been restored
		DevQueryUpComplete,		// device query for power-up complete
		DevQueryDown,			// see if device can power down
		DevQueryDownComplete,	// device query for power-down complete
		};

	static enum POWACTION actiontable[NUMPOWSTATES][NUMPOWEVENTS] = {
/*							NewIrp				MainIrpComplete				AsyncNotify	*/
/* InitialState */			{TriageNewIrp,		InvalidAction,				InvalidAction},
/* SysPowerUpPending */		{InvalidAction,		SysPowerUpComplete,			InvalidAction},
/* SubPowerUpPending */		{InvalidAction,		InvalidAction,				SubPowerUpComplete},
/* SubPowerDownPending */	{InvalidAction,		InvalidAction,				SubPowerDownComplete},
/* SysPowerDownPending */	{InvalidAction,		SysPowerDownComplete,		InvalidAction},
/* DevPowerUpPending */		{InvalidAction,		DevPowerUpComplete,			InvalidAction},
/* DevPowerDownPending */	{InvalidAction,		CompleteMainIrp,			InvalidAction},
/* ContextSavePending */	{InvalidAction,		InvalidAction,				ContextSaveComplete},
/* ContextRestorePending */	{InvalidAction,		InvalidAction,				ContextRestoreComplete},
/* DevQueryUpPending */		{InvalidAction,		DevQueryUpComplete,			InvalidAction},
/* DevQueryDownPending */	{InvalidAction,		DevQueryDownComplete,		InvalidAction},
/* QueueStallPending */		{InvalidAction,		InvalidAction,				QueueStallComplete},
/* FinalState */			{InvalidAction,		InvalidAction,				InvalidAction},
		};

	// Determine the first action to take based on the current state of the FSM and the event that occurred.
	// Note that this isn't as complicated as the use of 2-D array might suggest: all states except
	// the initial state lead to a single action for the one-and-only event that's possible to get in
	// that state.

	enum POWACTION action = actiontable[ctx->state][event];

	// Structurally, the following code is a switch on "action" imbedded within an
	// infinite loop. A case that does a "break" from the switch executes a "break"
	// from the loop, whereupon we return whatever value is left in "status". A case
	// that does a "continue" from the switch repeats the loop -- this is how actions
	// can be strung together during one call to this routine. I coded it this way to
	// avoid return statements in the middle that make it harder to prove that the
	// routine behaves in a predictable way. Note that any "break" should be preceded
	// by a change to the state recorded in the context structure and to the initially
	// invalid valid of "status". There are ASSERTs at the end to check this.

	// Concerning the required change to "ctx->state": there are many cases where we
	// call PoRequestPowerIrp or PoCallDriver, whereupon the context structure gets
	// released before those routines return. We use a SETSTATE macro so we don't
	// have to dereference a possibly invalid "ctx" pointer at the end of the loop. Any
	// action that calls a routine that might result in completing the current IRP
	// should also take care not to touch "ctx" afterwards. (These are always cases that
	// "break" from the switch, so you can just verify that the break always immediately
	// follows the PoXxx call.)

	// Concerning the required change to "status": only TriageNewIrp
	// will arrange to return STATUS_PENDING. Many of the other initial actions are entered
	// from a standard I/O completion routine and will need to return STATUS_MORE_PROCESSING_REQUIRED
	// to hold off final completion. Any action for MainIrpComplete that goes out through
	// CompleteMainIrp will end up returning ctx->status, which gets set in MainCompletionRoutine
	// to whatever's in the IRP -- this allows the IRP to complete normally. Any action off of
	// AsyncNotify should be changing "status" explicitly (and they do -- I checked).

#if DBG
	enum POWSTATE originalstate = ctx->state;
	enum POWSTATE nextstate = originalstate;
	#define SETSTATE(s) ctx->state = nextstate = s
#else
	#define SETSTATE(s) ctx->state = s
#endif

	while (TRUE)
		{						// handle this event
		switch (action)
			{					// perform next action

		///////////////////////////////////////////////////////////////////////
		// TriageNewIrp is the first action for a newly receive query or set IRP

		case TriageNewIrp:
			{					// TriageNewIrp
			ASSERT(stack->MajorFunction == IRP_MJ_POWER);
			ASSERT(stack->MinorFunction == IRP_MN_QUERY_POWER || stack->MinorFunction == IRP_MN_SET_POWER);
			ASSERT(ctx->state == InitialState);

			// We want the power dispatch routine to return STATUS_PENDING unless
			// something goes wrong right away. If we do return STATUS_PENDING, we
			// need to be sure we mark the IRP pending, 

			status = STATUS_PENDING;
			IoMarkIrpPending(Irp);

			// Acquire remove lock an extra time. We'll release it when we eventually
			// complete this IRP.

			IoAcquireRemoveLock(&pdx->RemoveLock, Irp);

			// For a system IRP, we'll request the corresponding device IRP. If system power is
			// being restored, we wait until the lower level drivers finish the system IRP. If
			// system power is being removed, we do it now and forward the system IRP when the
			// device IRP finishes.

			if (stack->Parameters.Power.Type == SystemPowerState)
				{				// system IRP
				if (stack->Parameters.Power.State.SystemState < pdx->syspower)
					{
					action = ForwardMainIrp;
					SETSTATE(SysPowerUpPending);
					}
				else
					{
					action = SelectDState;
					SETSTATE(SubPowerDownPending);
					}
				}				// system IRP

			// For a device set-power IRP, we have a variety of tasks to carry out. If device
			// power is being restored, we do those tasks when the lower level drivers complete
			// the IRP. If device power is being removed or staying the same, we do those tasks
			// before passing this IRP down. In either case, we ensure that the device isn't busy
			// with any substantive IRPs first.

			else
				{				// device IRP
				SETSTATE(QueueStallPending);

				action = QueueStallComplete;
				}				// device IRP

			continue;
			}					// TriageNewIrp
			
		///////////////////////////////////////////////////////////////////////
		// QueueStallComplete is the action for a MainIrpComplete event in th
		// QueueStallPending state. It's reached when StartNextPacket calls
		// GenericSaveRestoreComplete, which we specified as the current-irp
		// complete notification routine in our earlier call to StallRequestsAndNotify.
		// This action can also be reached directly from TriageNewIrp if the
		// device was idle to begin with or if we were already in a low-power
		// state (so that the queue should have been stalled)

		case QueueStallComplete:
			{					// QueueStallComplete
			if (stack->MinorFunction == IRP_MN_SET_POWER)
				{				// device set-power IRP
				if (stack->Parameters.Power.State.DeviceState < pdx->devpower)
					{
					action = ForwardMainIrp;
					SETSTATE(DevPowerUpPending);
					}
				else
					action = SaveContext;
				}				// device set-power IRP
			else
				{				// device query-power IRP
				if (stack->Parameters.Power.State.DeviceState < pdx->devpower)
					{
					action = ForwardMainIrp;
					SETSTATE(DevQueryUpPending);
					}
				else
					action = DevQueryDown;
				}				// device query-power IRP
			continue;
			}					// QueueStallComplete
			
		///////////////////////////////////////////////////////////////////////
		// ForwardMainIrp sends the current power IRP to the next driver in the
		// stack. We regain control in MainCompletionRoutine.

		case ForwardMainIrp:
			{					// ForwardMainIrp
			IoCopyCurrentIrpStackLocationToNext(Irp);
			IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) MainCompletionRoutine, (PVOID) ctx, TRUE, TRUE, TRUE);
			SafePoCallDriver(pdx->LowerDeviceObject, Irp); // avoid Win98 problem later on
			break;
			}					// ForwardMainIrp

		///////////////////////////////////////////////////////////////////////
		// SysPowerUpComplete is the action for a MainIrpComplete event in the
		// SysPowerUpPending state. If the IRP succeeded, request the corresponding
		// D-state IRP. When the subsidiary IRP finishes, we'll complete this
		// S-state IRP as well.
		//
		// The DDK doesn't explicitly say you need to send a D-state query when you
		// get an S-state query. It simplifies our own logic a good deal to do this,
		// however.

		case SysPowerUpComplete:
			{					// SysPowerUpComplete
			ASSERT(event == MainIrpComplete);

			if (!NT_SUCCESS(ctx->status))
				action = CompleteMainIrp;
			else
				{
				if (stack->MinorFunction == IRP_MN_SET_POWER)
					pdx->syspower = stack->Parameters.Power.State.SystemState;
				action = SelectDState;
				SETSTATE(SubPowerUpPending);
				status = STATUS_MORE_PROCESSING_REQUIRED;
				}

			continue;
			}					// SysPowerUpComplete

		///////////////////////////////////////////////////////////////////////
		// SysPowerDownComplete is the action for a MainIrpComplete event in the
		// SysPowerDownPending state.

		case SysPowerDownComplete:
			{					// SysPowerDownComplete
			if (stack->MinorFunction == IRP_MN_SET_POWER)
				pdx->syspower = stack->Parameters.Power.State.SystemState;

			action = CompleteMainIrp;
			continue;
			}					// SysPowerDownComplete

		///////////////////////////////////////////////////////////////////////
		// SelectDState is used to establish the power state and minor function
		// code for a D-state IRP that corresponds to the S-state IRP we're
		// processing. After doing that, we do the SendDeviceIrp action.

		case SelectDState:
			{					// SelectDState
			SYSTEM_POWER_STATE sysstate = stack->Parameters.Power.State.SystemState;

			// TODO In my testing, if I didn't go to D0 here, Win2K wouldn't come out
			// of suspend. Oddly enough, Win98SE automatically repowers the device the next time
			// a R/W IRP comes along if I just leave the device in D3. The DDK says
			// you can just leave the device depowered until another IRP comes along
			// so long as you're not an INRUSH device. It also says you must repower
			// yourself when you get a new IRP. This all needs more investigation...

			if (sysstate == PowerSystemWorking)
				ctx->devstate = PowerDeviceD0;
			else
				{
				DEVICE_POWER_STATE maxstate = pdx->devcaps.DeviceState[sysstate];
				DEVICE_POWER_STATE minstate = PowerDeviceD3;
				ctx->devstate = minstate > maxstate ? minstate : maxstate;
				}
			ctx->MinorFunction = stack->MinorFunction;
			action = SendDeviceIrp;
			continue;
			}					// SelectDState

		///////////////////////////////////////////////////////////////////////
		// SendDeviceIrp requests a device set- or query-power IRP using the power
		// state and minor function code currently in the context block. SelectDState
		// put them there.

		case SendDeviceIrp:
			{					// SendDeviceIrp

			// Win98 has a bug such that, if you request a set-power IRP for the same
			// D-state you're already in, PoRequestPowerIrp will report success but
			// CONFIGMG won't generate the configuration event that causes the IRP to
			// actually be sent. Without the following test, we would wait forever
			// for this expected IRP to complete.

			if (win98 && ctx->devstate == pdx->devpower)
				{				// pretend success
				ctx->status = STATUS_SUCCESS;
				action = actiontable[ctx->state][AsyncNotify];
				continue;
				}				// pretend success

			// Ask the power manager to send us an IRP. In Win98, we need to supply the
			// PDO as the device object address because NTKERN needs to go directly from
			// there to the devnode address.

			POWER_STATE powstate;
			powstate.DeviceState = ctx->devstate;

			NTSTATUS postatus = PoRequestPowerIrp(pdx->Pdo, ctx->MinorFunction, powstate,
				(PREQUEST_POWER_COMPLETE) PoCompletionRoutine, ctx, NULL);

			// If PoRequestPowerIrp fails, it never actually sent an IRP down the stack,
			// so we can certain that PoCompletionRoutine never ran

			if (NT_SUCCESS(postatus))
				break;			// started device IRP okay

			KdPrint((DRIVERNAME " - PoRequestPowerIrp failed - %X\n", postatus));
			action = CompleteMainIrp;
			ctx->status = postatus;
			continue;
			}					// SendDeviceIrp

		///////////////////////////////////////////////////////////////////////
		// CompleteMainIrp is the penultimate action of the finite state machine.
		// This is where we actually complete the power IRP we've been handling.

		case CompleteMainIrp:
			{					// CompleteMainIrp
			PoStartNextPowerIrp(Irp);

			// If called from MainCompletionRoutine, just allow the completion process
			// to take its course. Otherwise, explicitly complete the main IRP.

			if (event == MainIrpComplete)
				status = ctx->status;	// might have been STATUS_MORE_PROCESSING_REQUIRED until now
			else
				{
				ASSERT(ctx->status != STATUS_PENDING);
				Irp->IoStatus.Status = ctx->status;
				IoCompleteRequest(Irp, IO_NO_INCREMENT);
				}

			// Release the remove lock to balance the extra acquisition in TriageNewIrp
			
			IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
			
			action = DestroyContext;
			continue;
			}					// CompleteMainIrp

		///////////////////////////////////////////////////////////////////////
		// DestroyContext is the last action for an IRP.

		case DestroyContext:
			{					// DestroyContext
			SETSTATE(FinalState);
			ExFreePool(ctx);
			break;
			}					// DestroyContext

		///////////////////////////////////////////////////////////////////////
		// SubPowerUpComplete is the action for a AsyncNotify event in the
		// SubPowerUpPending state. This should be called from PoCompletionRoutine.
		// We can also get here from SendDeviceIrp to avoid the Win98 no-D-IRP bug,
		// in which case we don't want to alter "status" from its current value.

		case SubPowerUpComplete:
			{					// SubPowerUpComplete
			if (status == -1)
				status = STATUS_SUCCESS; // don't actually care, since called from PoCompletionRoutine
			action = CompleteMainIrp;
			continue;
			}					// SubPowerUpComplete

		///////////////////////////////////////////////////////////////////////
		// SubPowerDownComplete is the action for a AsyncNotify event in the
		// SubPowerDownPending state. This should be called from PoCompletionRoutine.
		// We can also get here from SendDeviceIrp to avoid the Win98 no-D-IRP bug,
		// in which case we don't want to alter "status" from its current value.

		case SubPowerDownComplete:
			{					// SubPowerDownComplete
			if (status == -1)
				status = STATUS_SUCCESS; // don't actually care, since called from PoCompletionRoutine

			if (NT_SUCCESS(ctx->status))
				{
				SETSTATE(SysPowerDownPending);
				action = ForwardMainIrp;
				}
			else
				action = CompleteMainIrp; // D-state IRP failed, so fail S-state IRP too
			
			continue;
			}					// SubPowerDownComplete

		///////////////////////////////////////////////////////////////////////
		// DevPowerUpComplete is the action for a MainIrpComplete event in the
		// DevPowerUpPending state. This should be called from MainCompletionRoutine
		// when a device power-up IRP finishes in the lower layers.

		case DevPowerUpComplete:
			{					// DevPowerUpComplete

			// If this IRP failed, or if we're just dealing with a query, we're done.

			if (!NT_SUCCESS(ctx->status) || stack->MinorFunction != IRP_MN_SET_POWER)
				{
				action = CompleteMainIrp;
				continue;
				}

			status = STATUS_MORE_PROCESSING_REQUIRED; // defer completion of the main IRP while we restore context

			ctx->oldpower = pdx->devpower;
			pdx->devpower = stack->Parameters.Power.State.DeviceState;

			KdPrint((DRIVERNAME " - Now in %s\n", devstate[pdx->devpower]));

			action = ContextRestoreComplete;
			continue;
			}					// DevPowerUpComplete

		///////////////////////////////////////////////////////////////////////
		// ContextRestoreComplete is the last action for a device set power up
		// operation. It's ordinarily reached when GenericSaveRestoreComplete
		// signals a MainIrpComplete event from the ContextRestorePending state.
		// It can also be reached directly from DevPowerUpComplete when there is
		// no context restore function.

		case ContextRestoreComplete:
			{					// ContextRestoreComplete
			if (event == AsyncNotify)
				status = STATUS_SUCCESS; // doesn't actually matter
			action = CompleteMainIrp;

			// If the device IRP failed, just go ahead and let it complete. If we've
			// successfully resumed to a sleeping state (> D0), skip restarting the
			// substantive IRP queue and complete the IRP as well.

			if (!NT_SUCCESS(ctx->status) || pdx->devpower != PowerDeviceD0)
				continue;

			ASSERT(stack->MinorFunction == IRP_MN_SET_POWER); // query should have gone directly to CompleteMainIrp from DevPowerUpComplete

			continue;
			}					// ContextRestoreComplete

		///////////////////////////////////////////////////////////////////////
		// SaveContext initiates a context save operation if necessary. This will
		// be the second action for a new device set-power IRP.

		case SaveContext:
			{					// SaveContext
			ASSERT(stack->MinorFunction == IRP_MN_SET_POWER);
			DEVICE_POWER_STATE devpower = stack->Parameters.Power.State.DeviceState;

			action = ContextSaveComplete;
			continue;
			}					// SaveContext

		///////////////////////////////////////////////////////////////////////
		// ContextSaveComplete is the action for an AsyncNotify event in the
		// ContextSavePending state. It should be entered from GenericSaveRestoreComplete,
		// which in turn should have been called by the client driver when its
		// context save operation finished. It can also be entered directly from
		// SaveContext when there is no context save routine.

		case ContextSaveComplete:
			{					// ContextSaveComplete
			if (event == AsyncNotify)
				status = STATUS_SUCCESS;	// doesn't actually matter in this case

			SETSTATE(DevPowerDownPending);
			action = ForwardMainIrp;

			ASSERT(stack);
			DEVICE_POWER_STATE devpower = stack->Parameters.Power.State.DeviceState;
			if (devpower <= pdx->devpower)
				continue;		// no actual change in device power

			ASSERT(stack->MinorFunction == IRP_MN_SET_POWER);

			pdx->devpower = devpower;

			KdPrint((DRIVERNAME " - Now in %s\n", devstate[pdx->devpower]));

			continue;
			}					// ContextSaveComplete

		///////////////////////////////////////////////////////////////////////
		// DevQueryUpComplete is the action for a MainIrpComplete event in the
		// DevQueryUpPending state. This should be called by MainCompletionRoutine
		// when a device query-power-up IRP completes. We don't expect to ever get this
		// kind of a query, by the way, but we should handle it nontheless.

		case DevQueryUpComplete:
			{					// DevQueryUpComplete
			if (NT_SUCCESS(ctx->status))
				{				// ask client if change okay

				// TODO replace the FALSE immediately below with some non-blocking test
				// to see if it's okay to restore power. It would be very unusual to
				// say "no". In making the test, pdx->devpower is the current power
				// state and stack->Parameters.Power.State.DeviceState is the
				// proposed new state.

				if (FALSE)
					ctx->status = STATUS_UNSUCCESSFUL; // fail the query
				}				// ask client if change okay

			action = CompleteMainIrp;
			continue;
			}					// DevQueryUpComplete

		///////////////////////////////////////////////////////////////////////
		// DevQueryDown is the second action (after TriageNewIrp) for a device
		// query-power that specifies less than or equal to the current device
		// power state.

		case DevQueryDown:
			{					// DevQueryDown
			DEVICE_POWER_STATE devpower = stack->Parameters.Power.State.DeviceState;

			// TODO replace the FALSE immediately below with some non-blocking test
			// to see if it's okay to remove power. In making the test, pdx->devpower
			// is the current power state and devpower is the proposed new state.

			if (devpower > pdx->devpower && FALSE)
				{				// fail the query
				ctx->status = STATUS_UNSUCCESSFUL;
				action = DevQueryDownComplete;
				continue;
				}				// fail the query

			SETSTATE(DevQueryDownPending);
			action = ForwardMainIrp;
			continue;
			}					// DevQueryDown

		///////////////////////////////////////////////////////////////////////
		// DevQueryDownComplete is the action for a MainIrpComplete event in the
		// DevQueryDownPending state. It can be reached from MainCompletionRoutine
		// or directly from DevQueryDown.

		case DevQueryDownComplete:
			{					// DevQueryDownComplete

			action = CompleteMainIrp;
			continue;
			}					// DevQueryDownComplete

		///////////////////////////////////////////////////////////////////////
		// InvalidAction is the action for any unexpected event. It should never occur.

		case InvalidAction:
		default:
			ASSERT(FALSE);
			status = STATUS_UNSUCCESSFUL;
			break;
			}					// perform next action

		break;					// for cases that "break" from the switch
		}						// handle this event

	// Check to make sure the state got changed before we exit
		
	ASSERT(nextstate != originalstate);

	// Check to make sure a valid status will be returned

	ASSERT(status != -1);

	return status;
	}							// HandlePowerEvent

///////////////////////////////////////////////////////////////////////////////

NTSTATUS MainCompletionRoutine(PDEVICE_OBJECT junk, PIRP Irp, PPOWCONTEXT ctx)
	{							// MainCompletionRoutine
	ctx->status = Irp->IoStatus.Status;
	return HandlePowerEvent(ctx, MainIrpComplete);
	}							// MainCompletionRoutine

VOID PoCompletionRoutine(PDEVICE_OBJECT junk, UCHAR fcn, POWER_STATE state, PPOWCONTEXT ctx, PIO_STATUS_BLOCK pstatus)
	{							// PoCompletionRoutine
	ctx->status = pstatus->Status;
	HandlePowerEvent(ctx, AsyncNotify);
	}							// PoCompletionRoutine

VOID PassivePowerCall(PIRP Irp)
	{							// PassivePowerCall
	PoCallDriver(IoGetNextIrpStackLocation(Irp)->DeviceObject, Irp);
	}							// PassivePowerCall

NTSTATUS SafePoCallDriver(PDEVICE_OBJECT DeviceObject, PIRP Irp)
	{							// SafePoCallDriver

	// If running in Win2K, or if Win98 and already at PASSIVE_LEVEL, just call
	// PoCallDriver.

	if (!win98 || KeGetCurrentIrql() == PASSIVE_LEVEL)
		return PoCallDriver(DeviceObject, Irp);
	
	// Win98's PoCallDriver is the same as IoCallDriver, and it won't do anything to
	// present the IRP at passive level if we're currently above. Build a work queue
	// item in the DriverContext field of the IRP and queue the work item so we
	// can present the IRP properly. Boy, is this something we shouldn't have to
	// worry about!

	IoMarkIrpPending(Irp);		// be sure it's marked pending
	IoGetNextIrpStackLocation(Irp)->DeviceObject = DeviceObject; // so PassivePowerCall can find it

	PWORK_QUEUE_ITEM item = (PWORK_QUEUE_ITEM) Irp->Tail.Overlay.DriverContext;
	ExInitializeWorkItem(item, (PWORKER_THREAD_ROUTINE) PassivePowerCall, (PVOID) Irp);
	ExQueueWorkItem(item, DelayedWorkQueue);

	return STATUS_PENDING;
	}							// SafePoCallDriver

