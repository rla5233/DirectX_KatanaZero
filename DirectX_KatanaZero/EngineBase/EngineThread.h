#pragma once
#include <thread>
#include <functional>
#include "NameObject.h"

// Ό³Έν :
class UEngineThread : public UNameObject
{
public:
	// constrcuter destructer
	UEngineThread();
	~UEngineThread();

	// delete Function
	UEngineThread(const UEngineThread& _Other) = delete;
	UEngineThread(UEngineThread&& _Other) noexcept = delete;
	UEngineThread& operator=(const UEngineThread& _Other) = delete;
	UEngineThread& operator=(UEngineThread&& _Other) noexcept = delete;

	void SetFunction(std::function<void()> _Function);

	void Start(std::function<void()> _Function = nullptr);

protected:
	std::thread Thread;
	std::function<void()> CallBack;

private:
	static void ThreadStartFunction(UEngineThread* _Thread);
};

