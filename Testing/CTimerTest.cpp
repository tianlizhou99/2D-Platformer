#include "pch.h"
#include "CppUnitTest.h"
#include "Timer.h"
#include "Game.h"
#include <memory>
#include "Element.h"
#include "Entity.h"
#include "XmlNode.h"
#include "player.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CTimerTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}

		TEST_METHOD(TestCTimerGettersSetters)
		{
			CGame game;
			/// add the timer to the game
			auto timer = std::make_shared<CTimer>(&game);

			game.SetTimer(5.00);

			Assert::IsTrue(timer->GetTime() == 5.00);

			game.SetTimer(0);
			
			Assert::IsTrue(timer->GetTime() == 0);
		}
		
		TEST_METHOD(TestCTimerUpdate)
		{
			CGame game;
			/// add the timer to the game
			auto timer = std::make_shared<CTimer>(&game);
			
			double time = timer->GetTime();

			Assert::IsTrue(time == 0);

			timer->Update(3.25);

			Assert::IsTrue(timer->GetTime() == 3.25);

			timer->Update(.50);

			Assert::IsTrue(timer->GetTime() == 3.75);

			timer->Update(.05245);

			Assert::IsTrue(timer->GetTime() == 3.80245);
		}
	};
}