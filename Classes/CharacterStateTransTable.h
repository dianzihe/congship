#ifndef _CHARACTERSTATETRANSTABLE_H__
#define _CHARACTERSTATETRANSTABLE_H__

//#include "base.h"

enum CharactorState
{
	eCharactorState_Idle = 0,//Õ¾Á¢²»¶¯	
	eCharactorState_Run,//ÅÜ
	eCharactorState_Attack,//¹¥»÷
	eCharactorState_UnderAttack,//ÊÜ»÷
	eCharactorState_Death, //ËÀÍö

#ifdef USED_JUMP
	eCharactorState_Jump,//ÆðÌø
	eCharactorState_DoubleJump,//2¶ÎÌø
	eCharactorState_Land,//ÂäµØ
#endif

	eCharactorState_Meditation,//´ò×ø

	eCharactorState_DeleteSelf,

	eCharactorState_Count,
};


class CharacterStateTransTable
{
public:
	CharacterStateTransTable()
	{
		/*
		memset(mCharacterStateTransTable[0], 0, sizeof(mCharacterStateTransTable) );
		mCharacterStateTransTable[eCharactorState_Idle][eCharactorState_Idle] = true;
		mCharacterStateTransTable[eCharactorState_Idle][eCharactorState_Run] = true;
		mCharacterStateTransTable[eCharactorState_Idle][eCharactorState_Attack] = true;
		mCharacterStateTransTable[eCharactorState_Idle][eCharactorState_UnderAttack] = true;
		mCharacterStateTransTable[eCharactorState_Idle][eCharactorState_Meditation] = true;
		mCharacterStateTransTable[eCharactorState_Idle][eCharactorState_Death] = true;

		mCharacterStateTransTable[eCharactorState_Run][eCharactorState_Idle] = true;
		mCharacterStateTransTable[eCharactorState_Run][eCharactorState_Run] = true;
		mCharacterStateTransTable[eCharactorState_Run][eCharactorState_Attack] = true;
		mCharacterStateTransTable[eCharactorState_Run][eCharactorState_UnderAttack] = true;
		mCharacterStateTransTable[eCharactorState_Run][eCharactorState_UnderAttack] = true;
		mCharacterStateTransTable[eCharactorState_Run][eCharactorState_Death] = true;

		mCharacterStateTransTable[eCharactorState_Attack][eCharactorState_Idle] = true;
		mCharacterStateTransTable[eCharactorState_Attack][eCharactorState_Attack] = true;
		mCharacterStateTransTable[eCharactorState_Attack][eCharactorState_Death] = true;
		mCharacterStateTransTable[eCharactorState_Attack][eCharactorState_Run] = true;

		mCharacterStateTransTable[eCharactorState_UnderAttack][eCharactorState_Attack] = true;
		mCharacterStateTransTable[eCharactorState_UnderAttack][eCharactorState_Death] = true;
		mCharacterStateTransTable[eCharactorState_UnderAttack][eCharactorState_Run] = true;

		mCharacterStateTransTable[eCharactorState_UnderAttack][eCharactorState_Idle] = true;

		mCharacterStateTransTable[eCharactorState_Death][eCharactorState_Idle] = true;

#ifdef USED_JUMP
		mCharacterStateTransTable[eCharactorState_Idle][eAnimation_Jump] = true;
		mCharacterStateTransTable[eCharactorState_Run][eAnimation_Jump] = true;
		mCharacterStateTransTable[eCharactorState_Attack][eAnimation_Jump] = true;
		mCharacterStateTransTable[eAnimation_Jump][eAnimation_DoubleJump] = true;
		mCharacterStateTransTable[eAnimation_Jump][eAnimation_Land] = true;
		mCharacterStateTransTable[eAnimation_DoubleJump][eAnimation_Land] = true;
		mCharacterStateTransTable[eAnimation_Land][eCharactorState_Idle] = true;
#endif
	*/
	}

	bool mCharacterStateTransTable[eCharactorState_Count][eCharactorState_Count];
};

#endif
