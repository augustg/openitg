#include "global.h"
#include "Judgment.h"
#include "GameState.h"

static ThemeMetric<apActorCommands>	RIDICULOUS_COMMAND		("Judgment","RidiculousCommand");
static ThemeMetric<apActorCommands>	MARVELOUS_COMMAND		("Judgment","MarvelousCommand");
static ThemeMetric<apActorCommands>	PERFECT_COMMAND			("Judgment","PerfectCommand");
static ThemeMetric<apActorCommands>	GREAT_COMMAND			("Judgment","GreatCommand");
static ThemeMetric<apActorCommands>	GOOD_COMMAND			("Judgment","GoodCommand");
static ThemeMetric<apActorCommands>	BOO_COMMAND			("Judgment","BooCommand");
static ThemeMetric<apActorCommands>	MISS_COMMAND			("Judgment","MissCommand");

static ThemeMetric<apActorCommands>	RIDICULOUS_ODD_COMMAND		("Judgment","RidiculousOddCommand");
static ThemeMetric<apActorCommands>	MARVELOUS_ODD_COMMAND		("Judgment","MarvelousOddCommand");
static ThemeMetric<apActorCommands>	PERFECT_ODD_COMMAND		("Judgment","PerfectOddCommand");
static ThemeMetric<apActorCommands>	GREAT_ODD_COMMAND		("Judgment","GreatOddCommand");
static ThemeMetric<apActorCommands>	GOOD_ODD_COMMAND		("Judgment","GoodOddCommand");
static ThemeMetric<apActorCommands>	BOO_ODD_COMMAND			("Judgment","BooOddCommand");
static ThemeMetric<apActorCommands>	MISS_ODD_COMMAND		("Judgment","MissOddCommand");

static ThemeMetric<apActorCommands>	RIDICULOUS_EVEN_COMMAND		("Judgment","RidiculousEvenCommand");
static ThemeMetric<apActorCommands>	MARVELOUS_EVEN_COMMAND		("Judgment","MarvelousEvenCommand");
static ThemeMetric<apActorCommands>	PERFECT_EVEN_COMMAND		("Judgment","PerfectEvenCommand");
static ThemeMetric<apActorCommands>	GREAT_EVEN_COMMAND		("Judgment","GreatEvenCommand");
static ThemeMetric<apActorCommands>	GOOD_EVEN_COMMAND		("Judgment","GoodEvenCommand");
static ThemeMetric<apActorCommands>	BOO_EVEN_COMMAND		("Judgment","BooEvenCommand");
static ThemeMetric<apActorCommands>	MISS_EVEN_COMMAND		("Judgment","MissEvenCommand");


Judgment::Judgment()
{
	m_iCount = 0;
}

void Judgment::Load( bool bBeginner )
{
	m_sprRidiculousJudgment.Load( THEME->GetPathG("Judgment", "LabelRidiculous") );

	m_sprJudgments.Load( THEME->GetPathG("Judgment",bBeginner?"BeginnerLabel":"label") );
	ASSERT( m_sprJudgments.GetNumStates() == 6 ||  m_sprJudgments.GetNumStates() == 12 );
	m_sprJudgments.StopAnimating();
	Reset();
	this->AddChild( &m_sprJudgments );
	this->AddChild( &m_sprRidiculousJudgment );
}

void Judgment::Reset()
{
	ResetSprite( m_sprJudgments );
	ResetSprite( m_sprRidiculousJudgment );
}

void Judgment::ResetSprite( Sprite& sprite )
{
	sprite.FinishTweening();
	sprite.SetXY( 0, 0 );
	sprite.SetEffectNone();
	sprite.SetHidden( true );
}

void Judgment::SetJudgment( TapNoteScore score, bool bEarly )
{
	Reset();

	bool spriteHasEarlyAndLateJudgments = m_sprJudgments.GetNumStates()==12;
	int iStateMult = ( spriteHasEarlyAndLateJudgments ) ? 2 : 1;
	int iStateAdd = ( bEarly || ( iStateMult == 1 ) ) ? 0 : 1;

	switch( score )
	{
	case TNS_RIDICULOUS:
	{
		int state = 0;
		ShowJudgmentFrame( m_sprRidiculousJudgment, state, RIDICULOUS_COMMAND, RIDICULOUS_ODD_COMMAND, RIDICULOUS_EVEN_COMMAND );
		break;
	}
	case TNS_MARVELOUS:
	{
		int state = 0 * iStateMult + iStateAdd;
		ShowJudgmentFrame( m_sprJudgments, state, MARVELOUS_COMMAND, MARVELOUS_ODD_COMMAND, MARVELOUS_EVEN_COMMAND );
		break;
	}
	case TNS_PERFECT:
	{
		int state = 1 * iStateMult + iStateAdd;
		ShowJudgmentFrame( m_sprJudgments, state, PERFECT_COMMAND, PERFECT_ODD_COMMAND, PERFECT_EVEN_COMMAND );
		break;
	}
	case TNS_GREAT:
	{
		int state = 2 * iStateMult + iStateAdd;
		ShowJudgmentFrame( m_sprJudgments, state, GREAT_COMMAND, GREAT_ODD_COMMAND, GREAT_EVEN_COMMAND );
		break;
	}
	case TNS_GOOD:
	{
		int state = 3 * iStateMult + iStateAdd;
		ShowJudgmentFrame( m_sprJudgments, state, GOOD_COMMAND, GOOD_ODD_COMMAND, GOOD_EVEN_COMMAND );
		break;
	}
	case TNS_BOO:
	{
		int state = 4 * iStateMult + iStateAdd;
		ShowJudgmentFrame( m_sprJudgments, state, BOO_COMMAND, BOO_ODD_COMMAND, BOO_EVEN_COMMAND );
		break;
	}
	case TNS_MISS:
	{
		int state = 5 * iStateMult + iStateAdd;
		ShowJudgmentFrame( m_sprJudgments, state, MISS_COMMAND, MISS_ODD_COMMAND, MISS_EVEN_COMMAND );
		break;
	}
	default:
		ASSERT(0);
	}

	m_iCount++;
}

void Judgment::ShowJudgmentFrame( Sprite& judgmentSprite, int state, ThemeMetric<apActorCommands>& cmd, ThemeMetric<apActorCommands>& oddCmd, ThemeMetric<apActorCommands>& evenCmd )
{
	judgmentSprite.SetState( state );
	judgmentSprite.RunCommands( (m_iCount%2) ? oddCmd : evenCmd );
	judgmentSprite.RunCommands( cmd );
	judgmentSprite.SetHidden( false );
}

/*
 * (c) 2001-2004 Chris Danford
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
