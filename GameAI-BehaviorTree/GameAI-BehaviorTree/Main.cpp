// GameAI-BehaviorTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BehaviorTree.h"
#include <random>
#include <functional>

int main()
{
	//������Ϊ������ɫһ��ʼ����Ѳ��״̬��һ�����ֵ��ˣ��ȼ���Լ�����ֵ�Ƿ���ͣ�����Ǿ����ܣ�����͹������ˣ������������������ֵ����Ҳ���жϹ������������ܣ������������������ֹͣ����
	BT::BehaviorTreeBuilder* Builder = new BT::BehaviorTreeBuilder();
	BT::BehaviorTree* Bt=Builder
		->ActiveSelector()
            ->Sequence()
	    	    ->Condition(BT::EConditionMode::IsSeeEnemy,false)
		             ->Back()       
		        ->ActiveSelector()
		             ->	Sequence()
		                  ->Condition(BT::EConditionMode::IsHealthLow,false)
           	                   ->Back()
		                  ->Action(BT::EActionMode::Runaway)
		                        ->Back()
		                  ->Back()
		            ->Parallel(BT::EPolicy::RequireAll, BT::EPolicy::RequireOne)
		                  ->Condition(BT::EConditionMode::IsEnemyDead,true)
		                        ->Back()
		                  ->Action(BT::EActionMode::Attack)
		                        ->Back()
		                  ->Back()
		           ->Back()
		        ->Back()
		->Action(BT::EActionMode::Patrol)
    ->End();

	delete Builder;

	//ģ��ִ����Ϊ��
	for (int i = 0; i < 10; ++i)
	{
		Bt->Tick();
		std::cout << std::endl;
	}

	Bt->Release();
	
	system("pause");
    return 0;
}

