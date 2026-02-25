#pragma once

class UInput
{
private:
	UInput()  = default;
	~UInput() = default;

	UInput(const UInput& rhs) = delete;
	UInput& operator=(const UInput& rhs) = delete;

public:
	bool Initialize();
	void Update();

	bool IsKeyDown(int vKey);
	bool IsKeyHeld(int vKey);
	bool IsKeyUp(int vKey);

public:
	static UInput& GetInstance()
	{
		static UInput Instance;
		return Instance;
	}

private:
	std::array<bool, 256> PreKeys;
	std::array<bool, 256> CurKeys;

};

