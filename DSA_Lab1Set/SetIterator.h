#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;
private:
	const Set& set;
	SetIterator(const Set& s);
	int index;

public:
	void first();
	void next();
	void previous();
	TElem getCurrent();
	bool valid() const;
};


