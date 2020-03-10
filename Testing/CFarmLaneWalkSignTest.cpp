#include "pch.h"
#include "CppUnitTest.h"
#include "Scoreboard.h"
#include "Game.h"
#include <memory>
#include "Element.h"
#include "Entity.h"
#include "XmlNode.h"
#include "FarmLaneWalkSign.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CFarmLaneWalkSignTest)
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

		TEST_METHOD(TestSignChange)
		{
			CGame game;
			CFarmLaneWalkSign sign(&game);

			Assert::IsTrue(sign.GetSign() == 0);
			
			sign.Update(6);
			Assert::IsTrue(sign.GetSign() == 1);

			sign.Update(6);
			Assert::IsTrue(sign.GetSign() == 0);
		}

	};
}