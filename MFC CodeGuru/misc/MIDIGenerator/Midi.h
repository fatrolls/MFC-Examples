#include "stdafx.h"

#define MIDI_SINGLETRACK           0
#define MIDI_MULTIPLETRACKS_SYNCH  1
#define MIDI_MULTIPLETRACKS_ASYNCH 2

#define MIDI_CHANNEL_0   0
#define MIDI_CHANNEL_1   1
#define MIDI_CHANNEL_2   2
#define MIDI_CHANNEL_3   3
#define MIDI_CHANNEL_4   4
#define MIDI_CHANNEL_5   5
#define MIDI_CHANNEL_6   6
#define MIDI_CHANNEL_7   7
#define MIDI_CHANNEL_8   8
#define MIDI_CHANNEL_9   9
#define MIDI_CHANNEL_10 10
#define MIDI_CHANNEL_11 11
#define MIDI_CHANNEL_12 12
#define MIDI_CHANNEL_13 13
#define MIDI_CHANNEL_14 14
#define MIDI_CHANNEL_15 15

#define MIDI_OCTAVE_0   0
#define MIDI_OCTAVE_1   1
#define MIDI_OCTAVE_2   2
#define MIDI_OCTAVE_3   3
#define MIDI_OCTAVE_4   4
#define MIDI_OCTAVE_5   5
#define MIDI_OCTAVE_6   6
#define MIDI_OCTAVE_7   7
#define MIDI_OCTAVE_8   8
#define MIDI_OCTAVE_9   9
#define MIDI_OCTAVE_10 10

#define MIDI_NOTE_C     0
#define MIDI_NOTE_C_    1
#define MIDI_NOTE_D     2
#define MIDI_NOTE_D_    3
#define MIDI_NOTE_E     4
#define MIDI_NOTE_F     5
#define MIDI_NOTE_F_    6
#define MIDI_NOTE_G     7
#define MIDI_NOTE_G_    8
#define MIDI_NOTE_A     9
#define MIDI_NOTE_A_   10
#define MIDI_NOTE_B    11

#define MIDI_MUSIC_MN   0 // Normale Musik
#define MIDI_MUSIC_ML   1 // Musik Legato
#define MIDI_MUSIC_MS   2 // Musik Staccato

//////////////////////////////////////////////////////////////////
// MidiFileHeader
//////////////////////////////////////////////////////////////////
struct CMidiFileHeader
{
	DWORD dwSignature;
	DWORD dwStructLength;
	WORD  wFileFormat;
	WORD  wTrackCount;
	WORD  wDeltaTimeTicks;

	CMidiFileHeader(WORD fileformat = MIDI_SINGLETRACK, WORD trackcount = 1, WORD deltatimeticks = 96);
	virtual void WriteToFile(ostream& os);
};

//////////////////////////////////////////////////////////////////
// MidiTrackHeader
//////////////////////////////////////////////////////////////////
struct CMidiTrackHeader
{
	DWORD dwSignature;
	DWORD dwTrackLength;

	CMidiTrackHeader(DWORD tracklength = 0);
	virtual void WriteToFile(ostream& os);
};

//////////////////////////////////////////////////////////////////
// MidiEventCommand
//////////////////////////////////////////////////////////////////
class CMidiEventCommand : public CObject
{
public:
	CMidiEventCommand(BYTE channel = 0, long deltatime = 0);
	virtual ~CMidiEventCommand();
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength()         {return 0;}; // should be overridden

	BYTE Channel;
	long DeltaTime;
};

class CMidiEventCommandNoteOff : public CMidiEventCommand
{
public:
	CMidiEventCommandNoteOff(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity);
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength()         {return 3;};

	BYTE Octave;
	BYTE NoteNumber;
	BYTE Velocity;
};

class CMidiEventCommandNoteOn : public CMidiEventCommand
{
public:
	CMidiEventCommandNoteOn(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity);
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength()         {return 3;};

	BYTE Octave;
	BYTE NoteNumber;
	BYTE Velocity;
};

class CMidiEventCommandKeyAfterTouch : public CMidiEventCommand
{
public:
	CMidiEventCommandKeyAfterTouch(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity);
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength()         {return 3;};

	BYTE Octave;
	BYTE NoteNumber;
	BYTE Velocity;
};

class CMidiEventCommandControlChange : public CMidiEventCommand
{
public:
	CMidiEventCommandControlChange(BYTE channel, long deltatime, BYTE controllernumber, BYTE newvalue);
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength()         {return 3;};

	BYTE ControllerNumber;
	BYTE NewValue;
};

class CMidiEventCommandProgramChange : public CMidiEventCommand
{
public:
	CMidiEventCommandProgramChange(BYTE channel, long deltatime, BYTE newprogramnumber);
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength()         {return 2;};

	BYTE NewProgramNumber;
};

class CMidiMetaEventCommand : public CMidiEventCommand
{
public:
	CMidiMetaEventCommand(BYTE command, BYTE datalen = 0, BYTE* data = NULL);
	virtual ~CMidiMetaEventCommand();
	virtual void WriteToFile(ostream& os);
	virtual DWORD GetLength();

	BYTE Command;
	long DataLen;
	BYTE* Data;
};

class CMidiMetaEventCommandEndOfTrack : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandEndOfTrack();
};

class CMidiMetaEventCommandTextEvent : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandTextEvent(const char* text);
};

class CMidiMetaEventCommandCopyrightNotice : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandCopyrightNotice(const char* copyrightnotice);
};

class CMidiMetaEventCommandTrackName : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandTrackName(const char* trackname);
};

class CMidiMetaEventCommandInstrumentName : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandInstrumentName(const char* instrumentname);
};

class CMidiMetaEventCommandLyric : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandLyric(const char* lyric);
};

class CMidiMetaEventCommandMarker : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandMarker(const char* marker);
};

class CMidiMetaEventCommandCuePoint : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandCuePoint(const char* cuepoint);
};

class CMidiMetaEventCommandMIDIChannelPrefix : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandMIDIChannelPrefix(BYTE cc);
};

class CMidiMetaEventCommandSetTempo : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandSetTempo(long tempo);
};

class CMidiMetaEventCommandTimeSignature : public CMidiMetaEventCommand
{
public:
	CMidiMetaEventCommandTimeSignature(BYTE nn, BYTE dd, BYTE cc, BYTE bb);
};

//////////////////////////////////////////////////////////////////
// MidiTrack
//////////////////////////////////////////////////////////////////
class CMidiTrack : public CCollection<CMidiEventCommand>
{
public:
	CMidiTrack();
	virtual void WriteToFile(ostream& os);

	// "Shortcuts"
	virtual void Copyright(const char* copyright);
	virtual void TimeSignature(BYTE nn, BYTE dd, BYTE cc, BYTE bb);
	virtual void Tempo(long tempo);
	virtual void NoteOn(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity);
	virtual void NoteOff(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity);
	virtual void Note(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE musicart = MIDI_MUSIC_MN, BYTE velocity = 96, BYTE vel_off = 64);
	virtual void Pause(BYTE channel, long deltatime);
	virtual void PlayString(BYTE channel, const char* playstring, BYTE velocity = 96, BYTE vel_off = 64);
	virtual void EndOfTrack();

	CMidiTrackHeader Header;
};

//////////////////////////////////////////////////////////////////
// MidiFile
//////////////////////////////////////////////////////////////////
class CMidiFile : public CCollection<CMidiTrack>
{
public:
	CMidiFile(WORD deltatimeticks, WORD fileformat = MIDI_SINGLETRACK, WORD trackcount = 1);
	virtual void WriteToFile(const char* filename);
	virtual void WriteToFile(ostream& os);

	CMidiFileHeader Header;
};

//////////////////////////////////////////////////////////////////
// SampleCode
//////////////////////////////////////////////////////////////////
void SampleCode();
