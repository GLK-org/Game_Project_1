#include "Level_controls.h"


class Temp : public Item {

public:
	Temp(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = false,
		bool combinable = false,
		bool consumable = false,
		States state = not_earned
	) : Item(gfx, spawnx, spawny, width, height, 1, interactable, combinable, consumable, state) {
		name = "Temp";
		LoadBmp(gfx, drawtarget, L"Bt.bmp");
		taggable = true;
	};
	Temp(const Item* act
	) : Item(act) {
		name = "Temp";

	}

	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"Bt.bmp");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override{
		return Item::LoadBmpRes(gfx, IDB_BITMAP1);
	}
	void Use() override
	{

	}

};

class Battery : public Item {

public:
	Battery(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = true,
		bool combinable = true,
		bool consumable = false,
		States state = not_earned
		) : Item(gfx,spawnx,spawny,width,height,1,interactable,combinable,consumable,state) {
		name = "Battery";
		LoadBmp(gfx, drawtarget, L"Battery.png");
		taggable = true;
	};
	Battery(const Item* act
	) : Item(act) {
		name = "Battery";

	}

	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"Battery.png");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override {
		return Item::LoadBmpRes(gfx, IDB_PNG5);
	}
	void Use() override
	{

	}

};

class Gyro : public Item {

public:
	Gyro(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = true,
		bool combinable = false,
		bool consumable = true,
		States state = not_earned
		) : Item(gfx, spawnx, spawny, width, height, 2, interactable, combinable, consumable, state) {
		name = "Gyro";
		LoadBmp(gfx, drawtarget, L"Gyro.png");
		taggable = true;
	}
	Gyro(const Item* act
	) : Item(act) {
		name = "Gyro";

	}
	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"Gyro.png");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override {
		return	Item::LoadBmpRes(gfx, IDB_PNG19);
	}
	void Use() override
	{

	}

};

class Launcher : public Item {

public:
	Launcher(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = true,
		bool combinable = false,
		bool consumable = false,
		States state = not_earned
		) : Item(gfx, spawnx, spawny, width, height, 3, interactable, combinable, consumable, state) {
		name = "Launcher";
		LoadBmp(gfx, drawtarget, L"Gravity_gun.png");
		taggable = true;
	}
	Launcher(const Item* act
	) : Item(act) {
		name = "Launcher";

	}
	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"Gravity_gun.png");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override {
		return	Item::LoadBmpRes(gfx, IDB_PNG18);
	}
	void Use() override
	{

	}
};

class Shield : public Item {

public:
	Shield(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = true,
		bool combinable = false,
		bool consumable = false,
		States state = not_earned
		) : Item(gfx, spawnx, spawny, width, height, 4, interactable, combinable, consumable, state) {
		name = "Shield";
		LoadBmp(gfx, drawtarget, L"Shield.png");
		taggable = true;
	}
	Shield(const Item* act
	) : Item(act) {
		name = "Shield";

	}

	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"Shield.png");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override {
		return	Item::LoadBmpRes(gfx, IDB_PNG33);
	}
	void Use() override
	{

	}
};

class ActiveShield : public Item {

public:
	ActiveShield(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = false,
		bool combinable = false,
		bool consumable = true,
		States state = not_earned
	) : Item(gfx, spawnx, spawny, width, height, 5, interactable, combinable, consumable, state) {
		name = "Active Shield";
	}

	ActiveShield(const Item * act
	) : Item(act) {
		name = "Active Shield";

	}
	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"ActiveShield.png");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override {
		return	Item::LoadBmpRes(gfx, IDB_PNG1);
	}
	void Use() override
	{

	}
};

class Keycard : public Item {

public:
	Keycard(
		Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		bool interactable = false,
		bool combinable = false,
		bool consumable = true,
		States state = not_earned
	) : Item(gfx, spawnx, spawny, width, height, 5, interactable, combinable, consumable, state) {
		name = "Keycard";
	}

	Keycard(const Item* act
	) : Item(act) {
		name = "Keycard";

	}
	void LoadBMP(Graphics* gfx) {
		LoadBmp(gfx, drawtarget, L"Bt.bmp");
	}
	HRESULT LoadBmpRes(Graphics* gfx, int ind = 0, bool sup = false) override {
		return	Item::LoadBmpRes(gfx, IDB_BITMAP1);
	}
	void Use() override
	{

	}

};

