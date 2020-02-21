#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include <memory>
#include "Element.h"
#include "Entity.h"
#include "XmlNode.h"
#include "player.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CGameTest)
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

		TEST_METHOD(TestGameScoreGettersSetters)
		{
			// This is an empty test just to ensure the system is working

			CGame game;

			game.SetScore(100);

			Assert::AreEqual(100,game.GetScore(),0.000001);

			game.SetScore(1000);

			Assert::AreEqual(1000, game.GetScore(), 0.000001);

			
		}

	};
}