#include "stdafx.h"
#include "BehaviorTreeEvent.h"
#include<assert.h>

using namespace BTEvent;

void BehaviorTree::Tick()
{
	//�����½�����ǲ��������б�
	Behaviors.push_back(nullptr);
	while (Step())
	{
	}
}

bool BehaviorTree :: Step()
{
	Behavior* Current = Behaviors.front();
	Behaviors.pop_front();
	//����������½��������ֹͣ
	if (Current == nullptr)
		return false;
	//ִ����Ϊ����
	Current->Tick();
	//�����������ֹ��ִ�м�캯��
	if (Current->IsTerminate() && Current->Observer)
	{
		Current->Observer(Current->GetStatus());
	}
	//�����������еȴ��´�tick����
	else
	{
		Behaviors.push_back(Current);
	}
}

void BehaviorTree::Start(Behavior* Bh, BehaviorObserver* Observe)
{
	if (Observe)
	{
		Bh->Observer = *Observe;
	}
	Behaviors.push_front(Bh);
}
void BehaviorTree::Stop(Behavior* Bh, EStatus Result)
{
	assert(Result != EStatus::Running);
	Bh->SetStatus(Result);
	if (Bh->Observer)
	{
		Bh->Observer(Result);
	}
}





