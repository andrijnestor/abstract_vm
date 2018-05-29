
#include "COperand.hpp"
#include "Operand.hpp"

COperand::COperand() {
	typedef std::pair<eOperandType, IOperand const* (COperand::*)(std::string const &v) const> mapEl;
	_creationMap.insert(mapEl(Int8, &COperand::createInt8));
	_creationMap.insert(mapEl(Int16, &COperand::createInt16));
	_creationMap.insert(mapEl(Int32, &COperand::createInt32));
	_creationMap.insert(mapEl(Float, &COperand::createFloat));
	_creationMap.insert(mapEl(Double, &COperand::createDouble));
}

COperand::COperand(COperand const &r){
	static_cast<void>(r);
}

COperand &COperand::operator=(COperand const &r){
	static_cast<void>(r);
	return *this;
}
COperand::~COperand(){

}

IOperand const *COperand::createOperand(eOperandType const &t, std::string val) const {
	auto f = _creationMap.at(t);
	return ((*this.*f)(val));
}

IOperand const *COperand::createInt8(std::string const &v) const {
	return new Operand<int8_t>(v, Int8, int8Precision);
}
IOperand const *COperand::createInt16(std::string const &v) const {
	return new Operand<int16_t>(v, Int16, int16Precision);
}
IOperand const *COperand::createInt32(std::string const &v) const {
	return new Operand<int32_t>(v, Int32, int32Precision);
}
IOperand const *COperand::createFloat(std::string const &v) const {
	return new Operand<float>(v, Float, floatPrecision);
}
IOperand const *COperand::createDouble(std::string const &v) const {
	return new Operand<double>(v, Double, doublePrecision);
}
