#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include "EngineEditorGUI.h"

#include "Level.h"
#include "GameMode.h"

#include "EngineVertexBuffer.h"

UEngineCore::UEngineCore() 
{
}

UEngineCore::~UEngineCore() 
{
	// ������ �����Ҷ� ���� ���� �ɼ��� ���̺� �ϰ� �Ѵ�.
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
	// ��üũ
	LeakCheck;
	GEngine = this;

	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	// ����̽� �ʱ�ȭ���� ũ�Ⱑ ���������� �ػ󵵰� �̹� ���� �Ȱſ���.
	// EngineOption.WindowScale �ػ�
	// �ػ󵵴� ������ ũ��� ������ �����ϴ�.
	EngineWindow.SetWindowScale(EngineOption.WindowScale);
	EngineDevice.Initialize(EngineWindow, EngineOption.ClearColor);

	UEngineEditorGUI::GUIInit();

	UEngineEditorGUI::CreateEditorWindow<UEngineDebugMsgWindow>("DebugMsgWindow");

	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}


	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineFrameUpdate, this),
		std::bind(&UEngineCore::EngineEnd, this)
	);

	UEngineEditorGUI::GUIRelease();
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

	// ȭ�� �����
	EngineDevice.RenderStart();
	// ���ӿ� ��ҵ��� �׸���

	CurLevel->Render(DeltaTime);

	UEngineEditorGUI::GUIRender(DeltaTime);
	
	// ������ �׳� �׷�����.

	// ����Ѵ�
	EngineDevice.RenderEnd();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string& _Name, std::shared_ptr<AActor> _GameMode)
{
	std::shared_ptr <AGameMode> GameModePtr = std::dynamic_pointer_cast<AGameMode>(_GameMode);

	if (nullptr == GameModePtr)
	{
		MsgBoxAssert("������ ù ������Ʈ�� GameMode�� ��ӹ��� Ŭ������ �ƴմϴ�.");
		return nullptr;
	}

	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->PushActor(_GameMode);
	Levels[_Name] = Level;
	return Level;
}