#include "stat.h"

C_STAT::C_STAT()
	:vStats{}
{
}

C_STAT& C_STAT::operator=(const C_STAT& rhs)
{
	vStats = rhs.vStats;
	return *this;
}

C_STAT& C_STAT::operator=(const std::vector<float>& rhs)
{
	vStats = rhs;
	return *this;
}

const C_STAT C_STAT::operator+(const C_STAT& add)
{
	C_STAT cSum{};
	cSum.vStats.resize(StatsMax);
	for (int i = 0; i < StatsMax; i++)
	{
		cSum.vStats.at(i) = add.vStats.at(i) + vStats.at(i);
	}
	return cSum;
}

C_STAT& C_STAT::operator+=(const C_STAT& add)
{
	for (int i = 0; i < StatsMax; i++)
	{
		vStats.at(i) += add.vStats.at(i);
	}
	return *this;
}

const C_STAT C_STAT::operator*(const C_STAT& scale)
{
	C_STAT cProduct{};
	cProduct.vStats.resize(StatsMax);
	for (int i = 0; i < StatsMax; i++)
		cProduct.vStats.at(i) = scale.vStats.at(i) * vStats.at(i);
	for (int i = ScaleMax; i < StatsMax; i++)
		cProduct.vStats.at(i) = vStats.at(i - ScaleMax) * scale.vStats.at(i);
	return cProduct;
}

C_STAT& C_STAT::operator*=(const C_STAT& scale)
{
	for (int i = 0; i < ScaleMax; i++)
		vStats.at(i) *= scale.vStats.at(i);
	for (int i = ScaleMax; i < StatsMax; i++)
		vStats.at(i) = vStats.at(i - ScaleMax) * scale.vStats.at(i);
	return *this;
}

const C_STAT C_STAT::operator*(int scale)
{
	C_STAT cProduct{};
	cProduct.vStats.resize(StatsMax);
	for (int i = 0; i < ScaleMax; i++)
		cProduct.vStats.at(i) = vStats.at(i) * scale;
	for (int i = ScaleMax; i < StatsMax; i++)
		cProduct.vStats.at(i) = vStats.at(i - ScaleMax) * scale;
	return cProduct;
}

float C_STAT::getStat(E_STAT _kind)
{
	return vStats.at(_kind);
}

std::vector<float>& C_STAT::getStats()
{
	return vStats;
}

void C_STAT::setStat(E_STAT _kind, float _value)
{
	vStats.at(_kind) = _value;
}

void C_STAT::addStat(E_STAT _kind, float _value)
{
	vStats.at(_kind) += _value;
}