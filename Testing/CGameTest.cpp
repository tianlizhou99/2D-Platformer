#include "pch.h"
#include "CppUnitTest.h"
#include "Platform.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CGameTest)
	{
	public:
		
		TEST_METHOD(LoadPlatformTest)
		{
			CGame game1;
			game1.LoadPlatform(L"images/snowLeft.png", L"images/snowMid.png", L"images/snowRight.png", 768, 944, 96, 32);

			CGame game2;
			auto leftplatform = make_shared<CPlatform>(&game2, L"images/snowLeft.png");
			leftplatform->SetLocation(768 - 32, 944);
			auto rightplatform = make_shared<CPlatform>(&game2, L"images/snowRight.png");
			rightplatform->SetLocation(768 + 32, 944);
			auto midplatform = make_shared<CPlatform>(&game2, L"images/snowMid.png");
			midplatform->SetLocation(768, 944);
			game2.Add(leftplatform);
			game2.Add(rightplatform);
			game2.Add(midplatform);

		}

		TEST_METHOD(TestMoneyGetterSetters)
		{
			CGame game;

			Assert::IsTrue(game.GetScore() == 0);

			game.SetScore(100);

			Assert::IsTrue(game.GetScore() == 100);

			game.SetScore(1000);

			Assert::IsTrue(game.GetScore() == 1000);
		}

	};
}