#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/EngineTexture.h>
#include "Level.h"
#include "GameMode.h"

#include "EngineVertexBuffer.h"

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
	// 엔진이 종료할때 기존 엔진 옵션을 세이브 하고 한다.
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
	UEngineSerializer Ser;
	EngineOption.Serialize(Ser);
	File.Open(EIOOpenMode::Write, EIODataType::Text);
	File.Save(Ser);
}

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	// 릭체크
	LeakCheck;
	GEngine = this;

	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	// 디바이스 초기화전에 크기가 다정해지면 해상도가 이미 결정 된거에요.
	// EngineOption.WindowScale 해상도
	// 해상도는 윈도우 크기와 관련이 없습니다.
	EngineWindow.SetWindowScale(EngineOption.WindowScale);
	EngineDevice.Initialize(EngineWindow, EngineOption.ClearColor);


	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineFrameUpdate, this),
		std::bind(&UEngineCore::EngineEnd, this)
	);
}

void UEngineCore::EngineOptionInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	if (false == Dir.IsFile("EngineOption.EData"))
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		EngineOption.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		EngineOption.DeSerialize(Ser);
	}

}

void UEngineCore::EngineEnd()
{
	EngineDevice.EngineResourcesRelease();
}

void UEngineCore::EngineFrameUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);

	GEngine->EngineWindow.CalculateMouseUpdate(DeltaTime);

	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel.get());
		}

		NextLevel->LevelStart(CurLevel.get());

		CurLevel = NextLevel;



		NextLevel = nullptr;
	}

	CurLevel->Tick(DeltaTime);

	// 화면 지우고
	EngineDevice.RenderStart();
	// 게임에 요소들을 그리고

	CurLevel->Render(DeltaTime);

	// 억지로 그냥 그려본다.

	// 출력한다
	EngineDevice.RenderEnd();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string& _Name, std::shared_ptr<AActor> _GameMode)
{
	std::shared_ptr <AGameMode> GameModePtr = std::dynamic_pointer_cast<AGameMode>(_GameMode);

	if (nullptr == GameModePtr)
	{
		MsgBoxAssert("레벨의 첫 오브젝트가 GameMode를 상속받은 클래스가 아닙니다.");
		return nullptr;
	}

	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->PushActor(_GameMode);
	Levels[_Name] = Level;
	return Level;
}