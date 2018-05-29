#ifndef COPERAND_HPP
#define COPERAND_HPP
#include "IOperand.hpp"
#include <map>

enum ePrecision {
	int8Precision=0,
	int16Precision=0,
	int32Precision=0,
	floatPrecision=7,
	doublePrecision=14,
};

class COperand {
public:
	COperand();
	COperand(COperand const &);
	COperand &operator=(COperand const &);
	virtual ~COperand();
	IOperand const *createOperand(eOperandType const &t, std::string val) const;
private:
	IOperand const *createInt8(std::string const &v) const;
	IOperand const *createInt16(std::string const &v) const;
	IOperand const *createInt32(std::string const &v) const;
	IOperand const *createFloat(std::string const &v) const;
	IOperand const *createDouble(std::string const &v) const;
	std::map<eOperandType, IOperand const* (COperand::*)(std::string const &v) const> _creationMap;
};



#endif
