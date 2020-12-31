#include "stdafx.h"

#include <fstream.h>
#include "Collect.h"
#include "Midi.h"

#pragma warning ( disable : 4244 )

void WriteWORDToFile(ostream& os, WORD value)
{
	WORD j = value;
	const char* ptr = (const char*)(&value);
	os.write(ptr+1, 1);
	os.write(ptr, 1);
}

void WriteDWORDToFile(ostream& os, DWORD value)
{
	DWORD j = value;
	const char* ptr = (const char*)(&value);
	os.write(ptr+3, 1);
	os.write(ptr+2, 1);
	os.write(ptr+1, 1);
	os.write(ptr+0, 1);
}

void WriteVarLen(ostream& os, long value)
{
	if (value < 0) return; // not supported
	long buffer;
	buffer = value & 0x7F;
	while ((value >>= 7) > 0)
	{
		buffer <<= 8;
		buffer |= 0x80;
		buffer += (value & 0x7F);
	}
	while (true)
	{
		char c = buffer & 0xFF;
		os.put(c);
		if (buffer & 0x80)
			buffer >>= 8;
		else
			break;
	}
}

long VarLenLen(long value)
{
	if (value < 0) return 0; // not supported
	long buffer;
	long ret = 0;
	buffer = value & 0x7F;
	while ((value >>= 7) > 0)
	{
		buffer <<= 8;
		buffer |= 0x80;
		buffer += (value & 0x7F);
	}
	while (true)
	{
		char c = buffer & 0xFF;
		ret++;
		if (buffer & 0x80)
			buffer >>= 8;
		else
			break;
	}
	return ret;
}

//////////////////////////////////////////////////////////////////
// MidiFileHeader
//////////////////////////////////////////////////////////////////
CMidiFileHeader::CMidiFileHeader(WORD fileformat/* = MIDI_SINGLETRACK*/, WORD trackcount/* = 1*/, WORD deltatimeticks/* = 120*/)
{
	dwSignature = 0x4D546864;
	dwStructLength = 0x0000006; //sizeof(CMidiFileHeader);
	wFileFormat = fileformat;
	wTrackCount = trackcount;
	wDeltaTimeTicks = deltatimeticks;
}

void CMidiFileHeader::WriteToFile(ostream& os)
{
	WriteDWORDToFile(os, dwSignature);
	WriteDWORDToFile(os, dwStructLength);
	WriteWORDToFile(os, wFileFormat);
	WriteWORDToFile(os, wTrackCount);
	WriteWORDToFile(os, wDeltaTimeTicks);
}

//////////////////////////////////////////////////////////////////
// MidiTrackHeader
//////////////////////////////////////////////////////////////////
CMidiTrackHeader::CMidiTrackHeader(DWORD tracklength/* = 0*/)
{
	dwSignature = 0x4D54726B;
	dwTrackLength = tracklength;
}

void CMidiTrackHeader::WriteToFile(ostream& os)
{
	WriteDWORDToFile(os, dwSignature);
	WriteDWORDToFile(os, dwTrackLength);
}

//////////////////////////////////////////////////////////////////
// MidiEventCommand
//////////////////////////////////////////////////////////////////
CMidiEventCommand::CMidiEventCommand(BYTE channel, long deltatime) : Channel(channel), DeltaTime(deltatime)
{
}

CMidiEventCommand::~CMidiEventCommand()
{
}

void CMidiEventCommand::WriteToFile(ostream& os)
{
	if (DeltaTime >= 0)
		WriteVarLen(os, DeltaTime);
}

CMidiEventCommandNoteOff::CMidiEventCommandNoteOff(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity) 
	: CMidiEventCommand(channel, deltatime), Octave(octave), NoteNumber(notenumber), Velocity(velocity)
{
}

void CMidiEventCommandNoteOff::WriteToFile(ostream& os)
{
	CMidiEventCommand::WriteToFile(os);
	BYTE w = 0x80;
	w |= Channel;
	os.put(w);
	w = 12*Octave+NoteNumber;
	os.put(w);
	w = Velocity;
	os.put(w);
}

CMidiEventCommandNoteOn::CMidiEventCommandNoteOn(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity) 
	: CMidiEventCommand(channel, deltatime), Octave(octave), NoteNumber(notenumber), Velocity(velocity)
{
}

void CMidiEventCommandNoteOn::WriteToFile(ostream& os)
{
	CMidiEventCommand::WriteToFile(os);
	BYTE w = 0x90;
	w |= Channel;
	os.put(w);
	w = 12*Octave+NoteNumber;
	os.put(w);
	w = Velocity;
	os.put(w);
}

CMidiEventCommandKeyAfterTouch::CMidiEventCommandKeyAfterTouch(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity)
	: CMidiEventCommand(channel, deltatime), Octave(octave), NoteNumber(notenumber), Velocity(velocity)
{
}

void CMidiEventCommandKeyAfterTouch::WriteToFile(ostream& os)
{
	CMidiEventCommand::WriteToFile(os);
	BYTE w = 0xA0;
	w |= Channel;
	os.put(w);
	w = 12*Octave+NoteNumber;
	os.put(w);
	w = Velocity;
	os.put(w);
}


CMidiEventCommandControlChange::CMidiEventCommandControlChange(BYTE channel, long deltatime, BYTE controllernumber, BYTE newvalue)
	: CMidiEventCommand(channel, deltatime), ControllerNumber(controllernumber), NewValue(newvalue)
{
}

void CMidiEventCommandControlChange::WriteToFile(ostream& os)
{
	CMidiEventCommand::WriteToFile(os);
	BYTE w = 0xB0;
	w |= Channel;
	os.put(w);
	w = ControllerNumber;
	os.put(w);
	w = NewValue;
	os.put(w);
}

CMidiEventCommandProgramChange::CMidiEventCommandProgramChange(BYTE channel, long deltatime, BYTE newprogramnumber)
	: CMidiEventCommand(channel, deltatime), NewProgramNumber(newprogramnumber)
{
}

void CMidiEventCommandProgramChange::WriteToFile(ostream& os)
{
	CMidiEventCommand::WriteToFile(os);
	WORD w = 0xC000;
	w += Channel * 0x100;
	w += NewProgramNumber;
	WriteWORDToFile(os, w);
}

CMidiMetaEventCommand::CMidiMetaEventCommand(BYTE command, BYTE datalen, BYTE* data)
	: CMidiEventCommand(0, 0), Command(command), DataLen(datalen)
{
	if (DataLen > 0 && data != NULL)
	{
		Data = new BYTE[DataLen];
		memcpy(Data, data, DataLen);
	}
	else
	{
		DataLen = 0;
		Data = NULL;
	}
}

CMidiMetaEventCommand::~CMidiMetaEventCommand()
{
	delete Data;
}

DWORD CMidiMetaEventCommand::GetLength()
{
	return 2+VarLenLen(DataLen)+DataLen;
}

void CMidiMetaEventCommand::WriteToFile(ostream& os)
{
	BYTE c;
	CMidiEventCommand::WriteToFile(os);
	c = 0xFF;
	os.put(c);
	os.put(Command);
	WriteVarLen(os, DataLen);
	if (DataLen > 0)
	{
		os.write(Data, DataLen);
	}
}

CMidiMetaEventCommandEndOfTrack::CMidiMetaEventCommandEndOfTrack()
	: CMidiMetaEventCommand(0x2F)
{
	DeltaTime = -1;
}

CMidiMetaEventCommandTextEvent::CMidiMetaEventCommandTextEvent(const char* text)
	: CMidiMetaEventCommand(0x01, strlen(text), (BYTE*)text)
{
}

CMidiMetaEventCommandCopyrightNotice::CMidiMetaEventCommandCopyrightNotice(const char* copyrightnotice)
	: CMidiMetaEventCommand(0x02, strlen(copyrightnotice), (BYTE*)copyrightnotice)
{
}

CMidiMetaEventCommandTrackName::CMidiMetaEventCommandTrackName(const char* trackname)
	: CMidiMetaEventCommand(0x03, strlen(trackname), (BYTE*)trackname)
{
}

CMidiMetaEventCommandInstrumentName::CMidiMetaEventCommandInstrumentName(const char* instrumentname)
	: CMidiMetaEventCommand(0x04, strlen(instrumentname), (BYTE*)instrumentname)
{
}

CMidiMetaEventCommandLyric::CMidiMetaEventCommandLyric(const char* lyric)
	: CMidiMetaEventCommand(0x05, strlen(lyric), (BYTE*)lyric)
{
}

CMidiMetaEventCommandMarker::CMidiMetaEventCommandMarker(const char* marker)
	: CMidiMetaEventCommand(0x06, strlen(marker), (BYTE*)marker)
{
}

CMidiMetaEventCommandCuePoint::CMidiMetaEventCommandCuePoint(const char* cuepoint)
	: CMidiMetaEventCommand(0x07, strlen(cuepoint), (BYTE*)cuepoint)
{
}

CMidiMetaEventCommandMIDIChannelPrefix::CMidiMetaEventCommandMIDIChannelPrefix(BYTE cc)
	: CMidiMetaEventCommand(0x20, 1, &cc)
{
}

CMidiMetaEventCommandSetTempo::CMidiMetaEventCommandSetTempo(long tempo)
	: CMidiMetaEventCommand(0x51)
{
	DataLen = 3;
	Data = new BYTE[3];
	// Normierung
	tempo *= 500000;
	tempo /= 120;
	// Zerlegung in 3 Bytes
	Data[0] = (tempo & 0xFF0000) / 0x10000;//0x07;
	Data[1] = (tempo & 0xFF00) / 0x100;//0xA1;
	Data[2] = tempo & 0xFF;//0x20;
}

CMidiMetaEventCommandTimeSignature::CMidiMetaEventCommandTimeSignature(BYTE nn, BYTE dd, BYTE cc, BYTE bb)
	: CMidiMetaEventCommand(0x58)
{
	DataLen = 4;
	Data = new BYTE[4];
	Data[0] = nn;
	Data[1] = dd;
	Data[2] = cc;
	Data[3] = bb;
}

//////////////////////////////////////////////////////////////////
// MidiTrack
//////////////////////////////////////////////////////////////////
CMidiTrack::CMidiTrack()
{
}

void CMidiTrack::WriteToFile(ostream& os)
{
	Header.dwTrackLength = 0; // für 0xFF2F00
	for (long i=0; i<Count(); i++)
	{
		if (At(i))
		{
			Header.dwTrackLength += At(i)->GetLength();
			Header.dwTrackLength += VarLenLen(At(i)->DeltaTime);
		}
	}
	Header.WriteToFile(os);
	
	for (i=0; i<Count(); i++)
	{
		if (At(i))
		{
			At(i)->WriteToFile(os);
		}
	}
}

void CMidiTrack::Copyright(const char* copyright)
{
	Insert(new CMidiMetaEventCommandCopyrightNotice(copyright));
}

void CMidiTrack::TimeSignature(BYTE nn, BYTE dd, BYTE cc, BYTE bb)
{
	Insert(new CMidiMetaEventCommandTimeSignature(nn, dd, cc, bb));
}

void CMidiTrack::Tempo(long tempo)
{
	Insert(new CMidiMetaEventCommandSetTempo(tempo));
}

void CMidiTrack::NoteOn(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity)
{
	Insert(new CMidiEventCommandNoteOn (channel, deltatime, octave, notenumber, velocity));
}

void CMidiTrack::NoteOff(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE velocity)
{
	Insert(new CMidiEventCommandNoteOff(channel, deltatime, octave, notenumber, velocity));
}

void CMidiTrack::Note(BYTE channel, long deltatime, BYTE octave, BYTE notenumber, BYTE musicart, BYTE velocity, BYTE vel_off)
{
	double dx = 7/8;
	switch(musicart)
	{
	case MIDI_MUSIC_MN: dx = 0.875; break;
	case MIDI_MUSIC_ML: dx = 1.0; break;
	case MIDI_MUSIC_MS: dx = 0.75; break;
	}
	Insert(new CMidiEventCommandNoteOn (channel, 0, octave, notenumber, velocity));
	Insert(new CMidiEventCommandNoteOff(channel, deltatime*dx, octave, notenumber, vel_off));
	Insert(new CMidiEventCommandNoteOff(channel, deltatime*(1-dx), octave, notenumber, vel_off));
}

void CMidiTrack::Pause(BYTE channel, long deltatime)
{
	Insert(new CMidiEventCommandNoteOff(channel, deltatime, 0, 0, 0));
}

void CMidiTrack::EndOfTrack()
{
	Insert(new CMidiMetaEventCommandEndOfTrack);
}

void CMidiTrack::PlayString(BYTE channel, const char* playstr, BYTE velocity/* = 96*/, BYTE vel_off/* = 64*/)
{
	int i = 0;
	BYTE MusikArt = MIDI_MUSIC_MN;
	BYTE Octave = MIDI_OCTAVE_4;
	double d = 500;
	int Laenge = 4; // Viertel-Note
	while (i<strlen(playstr))
	{
		if (strnicmp(playstr+i, "MF", 2)==0)
		{
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "MB", 2)==0)
		{
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "MN", 2)==0)
		{
			MusikArt = MIDI_MUSIC_MN;
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "ML", 2)==0)
		{
			MusikArt = MIDI_MUSIC_ML;
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "MS", 2)==0)
		{
			MusikArt = MIDI_MUSIC_MS;
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "O0", 2)>=0 && strnicmp(playstr+i, "O9", 2)<=0)
		{
			Octave = atoi(playstr+i+1);
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "L10", 3)>=0 && strnicmp(playstr+i, "L64", 3)<=0)
		{
			if (playstr[i+2]>='0' && playstr[i+2]<='9')
			{
				Laenge = atoi(playstr+i+1);
				i += 3;
				continue;
			}
		}
		if (strnicmp(playstr+i, "L1", 2)>=0 && strnicmp(playstr+i, "L9", 2)<=0)
		{
			Laenge = atoi(playstr+i+1);
			i += 2;
			continue;
		}
		if (strnicmp(playstr+i, "P10", 3)>=0 && strnicmp(playstr+i, "P64", 3)<=0)
		{
			if (playstr[i+2]>='0' && playstr[i+2]<='9')
			{
				int PLaenge = atoi(playstr+i+1);
				i += 3;
				double dd = d/PLaenge;
				while (playstr[i]=='.')
				{
					dd *= 1.5;
					i++;
				}
				Pause(channel, dd);
				continue;
			}
		}
		if (strnicmp(playstr+i, "P1", 2)>=0 && strnicmp(playstr+i, "P9", 2)<=0)
		{
			int PLaenge = atoi(playstr+i+1);
			i += 2;
			double dd = d/PLaenge;
			while (playstr[i]=='.')
			{
				dd *= 1.5;
				i++;
			}
			Pause(channel, dd);
			continue;
		}
		if (strnicmp(playstr+i, "T100", 4)>=0 && strnicmp(playstr+i, "T255", 4)<=0)
		{
			if (playstr[i+2]>='0' && playstr[i+2]<='9' && playstr[i+3]>='0' && playstr[i+3]<='9')
			{
				int tempo = atoi(playstr+i+1);
				Tempo(tempo);
				i += 4;
				continue;
			}
		}
		if (strnicmp(playstr+i, "T32", 3)>=0 && strnicmp(playstr+i, "T99", 3)<=0)
		{
			if (playstr[i+2]>='0' && playstr[i+2]<='9')
			{
				int tempo = atoi(playstr+i+1);
				Tempo(tempo);
				i += 3;
				continue;
			}
		}
		if (playstr[i]=='>')
		{
			Octave++;
			i++;
			continue;
		}
		if (playstr[i]=='<')
		{
			Octave--;
			i++;
			continue;
		}
		if (strnicmp(playstr+i, "A", 1)>=0 && strnicmp(playstr+i, "G", 1)<=0)
		{
			bool kreuz = false;
			bool be = false;
			int punkt = 0;
			int IndivLaenge = Laenge;
			BYTE note = MIDI_NOTE_C;
			if (toupper(playstr[i])=='A') note = MIDI_NOTE_A;
			if (toupper(playstr[i])=='B') note = MIDI_NOTE_B;
			if (toupper(playstr[i])=='C') note = MIDI_NOTE_C;
			if (toupper(playstr[i])=='D') note = MIDI_NOTE_D;
			if (toupper(playstr[i])=='E') note = MIDI_NOTE_E;
			if (toupper(playstr[i])=='F') note = MIDI_NOTE_F;
			if (toupper(playstr[i])=='G') note = MIDI_NOTE_G;
			i++;
			while (1)
			{
				if (playstr[i] == '#' || playstr[i] == '+')
				{
					kreuz = true;
					i++;
					continue;
				}
				if (playstr[i] == '-')
				{
					be = true;
					i++;
					continue;
				}
				if (playstr[i] == '.')
				{
					punkt++;
					i++;
					continue;
				}
				if (strncmp(playstr+i, "10", 2)<=0 && strncmp(playstr+i, "64", 2)>=0)
				{
					if (playstr[i+1]>='0' && playstr[i+1]<='9')
					{
						IndivLaenge = atoi(playstr+i);
						i += 2;
						continue;
					}
				}
				if (strncmp(playstr+i, "1", 1)<=0 && strncmp(playstr+i, "9", 1)>=0)
				{
					IndivLaenge = atoi(playstr+i);
					i++;
					continue;
				}
				break;
			}
			double dd = d / IndivLaenge;
			while (punkt>0)
			{
				dd *= 1.5;
				punkt--;
			}
			if (kreuz)
				note++;
			if (be)
				note--;
			Note(channel, dd, Octave, note, MusikArt, velocity, vel_off);
			continue;
		}
		CString errmessage = _T("An der folgenden Stelle ist ein Fehler aufgetreten: ");
		errmessage += CString(playstr+i);
		AfxMessageBox(errmessage);
		break;
	}
}

//////////////////////////////////////////////////////////////////
// MidiFile
//////////////////////////////////////////////////////////////////
CMidiFile::CMidiFile(WORD deltatimeticks/* = 96*/, WORD fileformat /*= MIDI_SINGLETRACK*/, WORD trackcount/* = 1*/)
	: Header(fileformat, trackcount, deltatimeticks)
{
}

void CMidiFile::WriteToFile(const char* filename)
{
	ofstream os(filename);
	WriteToFile(os);
}

void CMidiFile::WriteToFile(ostream& os)
{
	Header.wTrackCount = CountNonZero();
	if (Header.wTrackCount > 1 && Header.wFileFormat == MIDI_SINGLETRACK)
	{
		Header.wFileFormat = MIDI_MULTIPLETRACKS_SYNCH;
	}
	Header.WriteToFile(os);
	
	for (long i=0; i<Count(); i++)
	{
		if (At(i))
		{
			At(i)->WriteToFile(os);
		}
	}
}

void SampleCode_Test()
{
	for (int j=0; j<=255; j++)
	{
		CMidiFile midifile(96);
		CMidiTrack* miditrack = new CMidiTrack;
		miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
		miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
		miditrack->Tempo(120);
		miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, j));

		miditrack->PlayString(MIDI_CHANNEL_2, "MBT180MNO4T180l4cO3l8agl4fl8gab-agfl2gl4al8fel4dl8efl2gl4cP4O4l4cO3l8agl4fl8gab-agfl2gl4al8faO4l4dl8cO3bO4l2cl4cO3l8c.l16cl4fl8f.l16gl4al8g.l16fl8g.l16al4MLgl8MNgP8l8c.l16cl4fl8f.l16gl4al8g.l16fl8g.l16al4MLgl8MNgP8l8a.l16b-O4l4cO3l8aO4cO3l4fl8gab-O4cdcO3l4b-l8agl4al8gfl4gl8fel2MLfl8MNfP8P4");

		miditrack->EndOfTrack();
		midifile.Insert(miditrack);
		CString str;
		str.Format("Test%03d", j);
		midifile.WriteToFile(str);
	}
}

void SampleCode()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	miditrack->PlayString(MIDI_CHANNEL_2, "MBT120MNO3l8dg.l16gl4gP8l8ab.l16bl4b.l8babO4l4cO3f#agP8O4l8ddO3bO4l4e.l8dd.l16cl4c.l8ccO3aO4l4d.l8cc.O3l16bl4bP8l8dg.l16gl4gP8l8ab.l16bl4b.l8babO4l4cO3f#ag");

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("OTannenbaum.mid"));
}

void SampleCode_Pioniere()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	miditrack->PlayString(MIDI_CHANNEL_2, "MBT180MNO4T180l4cO3l8agl4fl8gab-agfl2gl4al8fel4dl8efl2gl4cP4O4l4cO3l8agl4fl8gab-agfl2gl4al8faO4l4dl8cO3bO4l2cl4cO3l8c.l16cl4fl8f.l16gl4al8g.l16fl8g.l16al4MLgl8MNgP8l8c.l16cl4fl8f.l16gl4al8g.l16fl8g.l16al4MLgl8MNgP8l8a.l16b-O4l4cO3l8aO4cO3l4fl8gab-O4cdcO3l4b-l8agl4al8gfl4gl8fel2MLfl8MNfP8P4");

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("Pioniere.mid"));
}

void SampleCode_Brueder()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	miditrack->PlayString(MIDI_CHANNEL_2, "MBT120MNO3l4e.l8f#l4ec#a.l8bl4af#e.l8f#l4ec#O2l2b.P4O3l4e.l8f#l4ec#a.l8bl4af#g#.l8al4g#f#l2e.P4l4a.l8al4aaaec#ef#.l8f#l4f#al2g#.P4l4a.l8al4aabag#f#e.l8el4f#g#l2a.P4l4a.l8al4aabO4c#edc#.O3l8aO4l4c#O3bl2a.P4");

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("Brüder.mid"));
}

void SampleCode_GehVoran()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	miditrack->PlayString(MIDI_CHANNEL_2, "MBT130MNO3T130l8MNfdl4cl8fgl4al8fdccfgl4al8fgl4aO4l8cO3b-l4afdcP4l8fdl4cl8fgl4al8fdccfgl4al8fgl4aO4l8cO3b-l4acfP4P2O4l4cl8cO3b-ab-O4cdl4cl8cO3b-l4aP4O4l4cl8cO3b-ab-O4cdl4cl8cO3b-l4aP4O4l4cl8cde-dcO3b-O4l2cP4");

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("GehVoran.mid"));
}

void SampleCode_Fruehtau()
{
	//ifstream is("test.mus");
	//char buffer[1000];
	//memset(buffer, 0, sizeof(buffer));
	//is.getline(buffer, sizeof(buffer)-1);
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	miditrack->PlayString(MIDI_CHANNEL_2, "MBT120O3T120l8dl4gl8bdl4gl8bgl4al8a.l16al4aP8l8bO4l4cl8ccdcO3bal4bl8g.l16gl4gP8l8gO4c.l16cl8ccl4ecO3l8bbgbO4l4dO3l8bgl4dl8f#aO4l4cO3l8af#l4gggP8l8gO4c.l16cl8ccl4ecO3l8bbgbO4l4dO3l8bgl4dl8f#aO4l4cO3l8af#l4gggP8");
	//miditrack->PlayString(MIDI_CHANNEL_2, buffer);
	//miditrack->PlayString(MIDI_CHANNEL_2, "MBT130MNO3T130l8MNfdl4cl8fgl4al8fdccfgl4al8fgl4aO4l8cO3b-l4afdcP4l8fdl4cl8fgl4al8fdccfgl4al8fgl4aO4l8cO3b-l4acfP4P2O4l4cl8cO3b-ab-O4cdl4cl8cO3b-l4aP4O4l4cl8cO3b-ab-O4cdl4cl8cO3b-l4aP4O4l4cl8cde-dcO3b-O4l2cP4");
	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("Frühtau.mid"));
}

void SampleCode_HorchWas()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	BYTE octave = MIDI_OCTAVE_3; // Gegenwärtige Oktave
	double d = 500;    // Ganze Note, Konstante (DeltaTime)

//MBT120MN
//O3
	octave = MIDI_OCTAVE_3;
//T120
//l4MNd
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l8ga
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4b
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//O3
	octave = MIDI_OCTAVE_3;
//MLbMNa
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l2g
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_G);
//l4d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l8ga
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4ba
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l2g
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_G);
//P2
	miditrack->Pause(MIDI_CHANNEL_2, d/2);
//l4d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l8ga
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4b
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//O3
	octave = MIDI_OCTAVE_3;
//MLbMNa
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l2g
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_G);
//l4a
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l8MNaMNaMLaMNgf#g
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
//l2a
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_A);
//P2
	miditrack->Pause(MIDI_CHANNEL_2, d/2);
//l4e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//l8ee
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//l4a
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l8ab
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//l2gd
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_D);
//l4a
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l8aa
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//O4
	octave = MIDI_OCTAVE_4;
//l4d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//O3
	octave = MIDI_OCTAVE_3;
//a
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//l2b
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_B);
//P4
	miditrack->Pause(MIDI_CHANNEL_2, d/4);
//l4b
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//l8e.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_E);
//l16e
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_E);
//l8ee
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//l4g
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_G);
//l8MLf#MNe
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//l4MLd
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D, MIDI_MUSIC_ML);
//l8gMNb
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//l2dd
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_D);
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_D);
//l4c#d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C_);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l2e
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_E);
//l4dc
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C);
//O3
	octave = MIDI_OCTAVE_3;
//l2b
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_B);
//P4
	miditrack->Pause(MIDI_CHANNEL_2, d/4);
//l4b
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//l8e.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_E);
//l16e
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_E);
//l8ee
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//l4g
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_G);
//l8MLf#MNe
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//l4MLd
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D, MIDI_MUSIC_ML);
//l8gMNb
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//l2dd
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_D);
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_D);
//l4c#d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C_);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l2e
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_E);
//l4dc
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C);
//O3
	octave = MIDI_OCTAVE_3;
//l2b
	miditrack->Note(MIDI_CHANNEL_2, d/2, octave, MIDI_NOTE_B);
//P2
	miditrack->Pause(MIDI_CHANNEL_2, d/2);

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("HochAufDemGelbenWagen.mid"));
}

void SampleCode_DasWandern()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	BYTE octave = MIDI_OCTAVE_3; // Gegenwärtige Oktave
	double d = 500;    // Ganze Note, Konstante (DeltaTime)

	
//MB
//T70
//MN
//O3
	octave = MIDI_OCTAVE_3;
//T70
//l8ea.
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_A);
//l16e
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_E);
//l8c#de.
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_D);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_E);
//l16f#
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_F_);
//l8ea
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//O4
	octave = MIDI_OCTAVE_4;
//c#.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//l16b
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_B);
//l8ab
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//c#.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_C_);
//l16d
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_D);
//l8c#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//O4
	octave = MIDI_OCTAVE_4;
//l4MLc#
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C_, MIDI_MUSIC_ML);
//O3
	octave = MIDI_OCTAVE_3;
//MNba
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//P8
	miditrack->Pause(MIDI_CHANNEL_2, d/8);
//l8ebb
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//l16MLc#
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_C_, MIDI_MUSIC_ML);
//O3
	octave = MIDI_OCTAVE_3;
//MNb
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_B);
//MLa#
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_A_, MIDI_MUSIC_ML);
//MNb
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_B);
//l8g#beebb
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//l16MLc#
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_C_, MIDI_MUSIC_ML);
//O3
	octave = MIDI_OCTAVE_3;
//MNb
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_B);
//MLa#
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_A_, MIDI_MUSIC_ML);
//MNb
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_B);
//l8g#beef#g#ab
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//c#.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//l16b
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_B);
//l8a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//O4
	octave = MIDI_OCTAVE_4;
//c#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//l4e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//O3
	octave = MIDI_OCTAVE_3;
//e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//O4
	octave = MIDI_OCTAVE_4;
//e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//O3
	octave = MIDI_OCTAVE_3;
//l8e
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//O4
	octave = MIDI_OCTAVE_4;
//c#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//MLb
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B, MIDI_MUSIC_ML);
//O4
	octave = MIDI_OCTAVE_4;
//c#d
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_D);
//l16c#
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_C_);
//MLd
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_D, MIDI_MUSIC_ML);
//l8eMNc#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//O4
	octave = MIDI_OCTAVE_4;
//c#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//MLb
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B, MIDI_MUSIC_ML);
//O4
	octave = MIDI_OCTAVE_4;
//c#d
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_D, MIDI_MUSIC_ML);
//l16c#d
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_C_, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_D, MIDI_MUSIC_ML);
//l8eMNc#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//O3
	octave = MIDI_OCTAVE_3;
//aaMLg#MNbeg#MLaMNea
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G_, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G_);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A, MIDI_MUSIC_ML);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//O4
	octave = MIDI_OCTAVE_4;
//c#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_C_);
//l4MLe
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E, MIDI_MUSIC_ML);
//O3
	octave = MIDI_OCTAVE_3;
//MNg#a
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_G_);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_A);
//P8
	miditrack->Pause(MIDI_CHANNEL_2, d/8);

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("DasWandernIstDesMüllersLust.mid"));
}

void SampleCode_Katjuscha()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	BYTE octave = MIDI_OCTAVE_3; // Gegenwärtige Oktave
	double d = 500;    // Ganze Note, Konstante (DeltaTime)
	//BYTE velocity = 96;
	//BYTE vel_off = 64;

//O3l4e.
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_E, velocity);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_E);
//l8f#
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_F_, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
//l4g.
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_G, velocity);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_G);
//l8e g.
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_G);
//l16g
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_G, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_G);
//l8f# e
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_F_, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_E, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
//l4f#
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_F_, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_F_);
//O2
	octave = MIDI_OCTAVE_2;
//b
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_B, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//O3
	octave = MIDI_OCTAVE_3;
//f#.
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_F_, velocity);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_F_);
//l8g
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_G, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
//l4a.
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_A, velocity);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_A);
//l8f# a.
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_F_, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_A, velocity);
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/16, octave, MIDI_NOTE_A);
//l16a
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_A, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/16, octave, MIDI_NOTE_A);
//l8g f#
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_G, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_F_, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
//l4e
	//miditrack->NoteOn (MIDI_CHANNEL_2,   0, octave, MIDI_NOTE_E, velocity);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//P4
	miditrack->Pause(MIDI_CHANNEL_2, d/4);
//l4b
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//e d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l8e d
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_D);
//l4c
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C);
//O3
	octave = MIDI_OCTAVE_3;
//l8b a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4b e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//O4
	octave = MIDI_OCTAVE_4;
//c.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_C);
//O3
	octave = MIDI_OCTAVE_3;
//l8a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4b.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_B);
//l8g a a g f#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
//l4e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//P4
	miditrack->Pause(MIDI_CHANNEL_2, d/4);
//l4b
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
//O4
	octave = MIDI_OCTAVE_4;
//e d
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_D);
//l8e d
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_E);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_D);
//l4c
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_C);
//O3
	octave = MIDI_OCTAVE_3;
//l8b a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4b e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_B);
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//O4
	octave = MIDI_OCTAVE_4;
//c.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_C);
//O3
	octave = MIDI_OCTAVE_3;
//l8a
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
//l4b.
	miditrack->Note(MIDI_CHANNEL_2, (d*3)/8, octave, MIDI_NOTE_B);
//l8g a a g f#
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_A);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_G);
	miditrack->Note(MIDI_CHANNEL_2, d/8, octave, MIDI_NOTE_F_);
//l4e
	miditrack->Note(MIDI_CHANNEL_2, d/4, octave, MIDI_NOTE_E);
//P4
	miditrack->Pause(MIDI_CHANNEL_2, d/4);

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("Katjuscha.mid"));
}
/*
G-Dur
MBT120MN
O3l4e.
l8f#
l4g.
l8e g.
l16g
l8f# e
l4f#
O2
b
O3
f#.
l8g
l4a.
l8f# a.
l16a
l8g f#
l4e
P4
l4b
O4
e d
l8e d
l4c
O3
l8b a
l4b e
O4
c.
O3
l8a
l4b.
l8g a a g f#
l4e
P4
l4b
O4
e d
l8e d
l4c
O3
l8
b a
l4b e
O4
c.
O3
l8a
l4b.
l8g a a g f#
l4e
P4
*/
//////////////////////////////////////////////////////////////////
// SampleCode
//////////////////////////////////////////////////////////////////
void SampleCode1()
{
	CMidiFile midifile(96);
	CMidiTrack* miditrack = new CMidiTrack;
	miditrack->Copyright(_T("Copyright (C) 1997 Andreas Jaeger"));
	miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
	miditrack->Tempo(120);
	miditrack->Insert(new CMidiEventCommandProgramChange (MIDI_CHANNEL_2, 0, 70));

	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_C,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_C,  64);

	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_D,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_D,  64);
	
	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_E,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_E,  64);

	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_F,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_F,  64);

	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_G,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_G,  64);

	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_A,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_A,  64);

	miditrack->NoteOn (MIDI_CHANNEL_2,   0, MIDI_OCTAVE_4, MIDI_NOTE_B,  96);
	miditrack->NoteOff(MIDI_CHANNEL_2, 192, MIDI_OCTAVE_4, MIDI_NOTE_B,  64);

	miditrack->EndOfTrack();
	midifile.Insert(miditrack);
	midifile.WriteToFile(_T("test.mid"));
}

#pragma warning ( default : 4244 )
