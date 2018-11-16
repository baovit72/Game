#pragma once
#ifndef WeaponSystem_H_
#define WeaponSystem_H_
#include<list>
#include"Speedburner.h"

class WeaponSystem
{
private:
	std::list<Bullet*> WeaponMegaman;
	std::list<Bullet*> WeaponEnemy;

	static WeaponSystem* instance;
public:
	WeaponSystem();
	~WeaponSystem();

	static WeaponSystem* Instance();

	void Update(DWORD dt, vector<Object*> *List_object_can_col);
	void Render();

	std::list<Bullet*> GetListWeaponMegaman();
	std::list<Bullet*> GetListWeaponEnemy();

	void AddBulletMegaman(Bullet* bullet);
	void AddBulletEnemy(Bullet* bullet);
};


#endif // !WeaponSystem_H_