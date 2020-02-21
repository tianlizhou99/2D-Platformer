#include "pch.h"
#include "CppUnitTest.h"
#include "Scoreboard.h"
#include "Game.h"
#include <memory>
#include "Element.h"
#include "Entity.h"
#include "XmlNode.h"
#include "player.h"
#include <President.h>
#include <Money.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CScoreboardTest)
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

		TEST_METHOD(TestScoreboardGetterSetters)
		{
			CGame game;

			Assert::IsTrue(game.GetScore() == 0);

			/// add the scoreboard to the game
			auto scoreboard = std::make_shared<CScoreboard>(&game);

			double score = scoreboard->GetScore();

			Assert::IsTrue(score == 0);

			game.SetScore(100);

			Assert::IsTrue(game.GetScore() == 100);

			game.SetScore(1000);

			Assert::IsTrue(game.GetScore() == 1000);
		}

		TEST_METHOD(TestCScoreboardTuitionIncrease)
		{
			CGame game;
			/// add the scoreboard to the game
			auto scoreboard = std::make_shared<CScoreboard>(&game);
			auto player = std::make_shared<CPlayer>(&game);
			wstring presImage = L"images/stanley.png";
			auto president = std::make_shared<CPresident>(&game, presImage);


			// Force player to collide with president
			player->SetLocation(10, 10);
			president->SetLocation(10, 10);
			game.CollisionTest(player.get());

			// Force player to collide with money
			wstring moneyImage = L"images/money100.png";
			auto money = std::make_shared<CMoney>(&game, moneyImage);
			money->SetLocation(10, 10);
			game.CollisionTest(player.get());

			// Check if tuition Increased
			double score = scoreboard->GetScore();
			Assert::IsTrue(score == 110);
		}
	};
}