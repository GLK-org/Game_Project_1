#pragma once
#include "Primitives.h"
#include "GameController.h"
#include <E:\VS_projects\Game_engine_1\resources\resource.h>
//#include "Converter.h"
#define CENTER_Y ((WNDHEIGHT*7)/8- WNDHEIGHT/100)
#define CENTER_X ((WNDWIDTH*3)/4)
#define WIDTH_ITEM ((WNDWIDTH + WNDWIDTH / 8 )/2-WNDWIDTH/12)
#define HEIGHT_ITEM (WNDHEIGHT / 4)
#define STANDARD_PLAYER_POS WNDWIDTH / 4, WNDHEIGHT *60/ 100, WNDWIDTH/ 12.0f, WNDHEIGHT*2/10.0f



enum Objs {
	nl,
	Obj1,
	Obj2

};

enum States {
	not_earned,
	earned,
	in_use,
	used
};

class BaseUnknown {
public:

	Recta* drawtarget;
	Speed spd;
	std::string name;
	bool taggable;
	bool condition;
	BaseUnknown(std::string n = "NULL", bool tag = false);
	virtual ~BaseUnknown();
	virtual void SetSpd(Speed spd);

	virtual bool CheckTrigg(const POINT& p);
	virtual bool CheckTrigg(const D2D1_POINT_2F& p);
	virtual bool CheckTrigg(const D2D1_RECT_F& p);
	virtual void Update(float x=0, float y=0);
	virtual void Update(float x , float y, bool grav);
	virtual	void Update(POINT& p);
	virtual HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false)=0;
	bool operator==(BaseUnknown& base) {
		return (name == base.name ? true : false);
	}
	bool operator!=(BaseUnknown& base) {
		return (name != base.name ? true : false);
	}
	D2D1_POINT_2F Get_inv_veloc();
};

struct Player : public BaseUnknown {
	
    int speed;
	D2D1_POINT_2F feet;
	POINT targetloc;
	Player(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height
	);

	virtual ~Player();

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1);
	
	void RenderBmp(Graphics* gfx,
		FLOAT opacity,
		bool anim = false);

	void RenderSpecialBmp(Graphics* gfx,
		FLOAT opacity, std::wstring name,
		bool anim = false,
		Speed spd = F_IMMEDIATE, int startingframe = 0);

	HRESULT LoadBmp(Graphics* gfx, std::wstring name);
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;

	HRESULT LoadBmp(Graphics* gfx);
	void UpdateFeet();
	bool CheckPoint();
	void SetPoint(POINT& p);
	void MoveToPoint(POINT& p, float speed = FAST, bool grav=true);
	void Move(POINT& p, float speed, bool invol = false);
	void Move(POINT& p, float speed, D2D1_RECT_F* limit, bool grav=true);
	
};

struct Doors : public BaseUnknown {
	//Obiekt zdarzenia do kontroli blokady drzwi
	float wait, threshold;
	bool lopen, ropen;;
	Recta* left;
	Recta* right;
	Recta * wallsl;
	Recta* wallsr;
	int frame;
	int chosen;
	GameLevel* prev;
	GameLevel* next;
public:

	Doors(Graphics* gfx, GameLevel* prev = nullptr, GameLevel* next = nullptr);

	virtual ~Doors();

	//Zmiana poziomu bez udzia³u gracza
	bool UpdateTrig(POINT& p);

	//Zmiana poziomu z potrzeb¹ zbli¿enia siê postaci gracza do "drzwi"
	bool UpdateTrig(POINT& p, const Player& player);


	void Render(Graphics* gfx, POINT& p, float r, float g, float b, float a);
	
	HRESULT LoadBmp(Graphics* gfx);

	HRESULT LoadBmpRes(Graphics* gfx, int ind = IDB_PNG10, bool sup = false) override;
	HRESULT Doors::LoadBmpReswalls(Graphics* gfx, int ind);

	HRESULT LoadBmp(Graphics* gfx, std::wstring name);

};

struct Panel : public BaseUnknown{


	Recta* base;
	Recta* item_base;
	Recta* spaces[4];
	Recta* text_base;
	Recta* points;
	std::string pointsTxt, text_baseTxt;
	Panel(Graphics* gfx);
		
	virtual ~Panel();

	void DrawBmp(Graphics* gfx, Recta* obj, int frame = 0);


	HRESULT LoadBmp(Graphics* gfx, Recta* obj, std::wstring name = {}, bool bg = false);
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;
	HRESULT LoadBmpRes(Graphics* gfx, int ind, Recta* obj) ;
	void Render(Graphics* gfx);

	void DrawTxt(Graphics* gfx, Writer* wrt, D2D1_RECT_F rect, std::string inputtxt, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT par = DWRITE_PARAGRAPH_ALIGNMENT_NEAR, float val = -1);

	void SetText(std::string inputtxt, int choice);

	void LoadTextOnStuff(Graphics* gfx, Writer* wrt, int choice);

};

class BaseButton : public BaseUnknown {
public:
	Obj* ob;
	float r, g, b, a;
	std::string text;
	BaseButton(Obj* ob, float r, float g, float b, float a, std::string text = "0");
	virtual ~BaseButton();

	void Render(Graphics* gfx, float r, float g, float b, float a, bool wtext = false, Writer* wrt = { 0 }, bool colorable = false);
	bool CheckTrg(POINT& p);
	virtual void OnTrig() =0;
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;

};

class Item : public BaseUnknown {
public:

	int id;
	bool interactable, combinable, consumable;
	int state;



	Item(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int id = nl,
		bool interactable = false,
		bool combinable = false,
		bool consumable = false,
		States state = not_earned
	);

	Item(const Item* copying);
	virtual ~Item();

	virtual void Use() = 0;

	void RenderBmp(Graphics* gfx,

	FLOAT opacity, D2D1_RECT_F rec, bool anim = false);

	
	virtual HRESULT LoadBmpRes(Graphics* gfx, int ind=0, bool sup = false);

	virtual HRESULT LoadBmp(Graphics* gfx, Recta* obj, std::wstring name = {});
};

struct Ball : public BaseUnknown {
	POINT targetloc;
	Ball(Graphics* gfx,
		float spawnx,
		float spawny,
		float rad,
		float width,
		float height,
		std::string name = "NULL"
	);
	virtual ~Ball();

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1);
	
	void RenderBmp(Graphics* gfx,FLOAT opacity, bool anim = false);
	
	HRESULT LoadBmp(Graphics* gfx, std::wstring name = {});
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;
	void Update(float x, float y);

};

struct Inanimate : public BaseUnknown {
	bool traversible;
	bool solid;
	std::wstring texturefile;
	
	Inanimate(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int texturefile,
		bool traversible = false,
		bool solid = true,
		std::string name = "NULL",
		bool taggable = false
	);
	~Inanimate();

	bool getTrav();

	void setTrav(bool set);

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1);

	void RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim = false, int startingframe = 0);

	void RenderBmpBG(Graphics* gfx,
		FLOAT opacity, bool anim = false, int startingframe = 0);

	HRESULT LoadBmp(Graphics* gfx, std::wstring name = {}, bool bg = false);
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;
	HRESULT LoadBmp(Graphics* gfx, float width, float height, std::wstring name = {}, bool bg = false);


}; 

struct Animate : public BaseUnknown {

	bool traversible;
	bool solid;
	std::wstring texturefile;

	Animate(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		int texturefile,
		bool traversible = false,
		bool solid = true,
		std::string name = "NULL",
		bool taggable = false,
		float mass = 1.0f
	);
	~Animate();

	bool getTrav();

	void setTrav(bool set);

	void Render(Graphics* gfx, POINT& p, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1);

	void RenderBmp(Graphics* gfx,
		FLOAT opacity, bool anim = false);

	void RenderBmpBG(Graphics* gfx,
		FLOAT opacity, bool anim = false);

	HRESULT LoadBmp(Graphics* gfx, std::wstring name = {}, bool bg = false);
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;
	HRESULT LoadBmp(Graphics* gfx, float width, float height, std::wstring name = {}, bool bg = false);

	void Update(float x = 0.0f, float y = 0.0f);

	void Update(POINT& p);

	
};

struct FloatingText : public BaseUnknown {
	std::string text;
	int frame = 0; 
	FloatingText(Graphics* gfx,
		float spawnx,
		float spawny,
		float width,
		float height,
		std::string text
	);

	virtual ~FloatingText();

	void Render(Graphics* gfx, POINT& p, Writer* wrt = {}, bool fill = false, float r = 0.8f, float g = 0.5f, float b = 0.5f, float a = 1);
	
	void SetText(std::string inputtxt);
	HRESULT LoadBmpRes(Graphics* gfx, int ind, bool sup = false) override;
	void Update(POINT p);
};
