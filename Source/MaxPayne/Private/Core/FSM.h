// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define Create_FSM(ClassName, FSM_Data_Holder,Owner)\
template <typename FSM_Data_Holder>\
class ClassName\
{\
public:\
	FSM_Data_Holder PreviousState;\
	FSM_Data_Holder CurrentState;\
\
	ClassName(FSM_Data_Holder InitialState)\
	{\
		PreviousState = CurrentState = InitialState;\
	}\
\
private:\
	bool SwitchState(FSM_Data_Holder NewState)\
	{\
		if (CurrentState == NewState)\
		{\
			return false;\
		}\
\
		PreviousState = CurrentState;\
		CurrentState = NewState;\
\
		return true;\
	}\
\
	friend class Owner;\
};\
