#pragma once
#include <vector>
class C_STAT
{
public:
	enum E_STAT
	{
		MaxHealth,
		MaxMana,
		AttackPower,
		Armor,
		MagicPower,
		MagicResistance,
		HealthRegen, CurrentHealth = HealthRegen, ScaleMax = HealthRegen,
		ManaRegen, CurrentMana = ManaRegen,
		StatsMax
	};

private:
	std::vector<float> vStats;

public:
	C_STAT();
	C_STAT& operator=(const C_STAT& rhs);
	C_STAT& operator=(const std::vector<float>& rhs);
	const C_STAT operator+(const C_STAT& add);
	C_STAT& operator+=(const C_STAT& add);
	const C_STAT operator*(const C_STAT& scale);
	C_STAT& operator*=(const C_STAT& scale);
	const C_STAT operator*(int scale);

	float getStat(E_STAT _kind);
	std::vector<float>& getStats();
	void setStat(E_STAT _kind, float _value);
	void addStat(E_STAT _kind, float _value);
};