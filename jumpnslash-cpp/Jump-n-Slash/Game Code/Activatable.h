#ifndef ACTIVATABLE_H
#define ACTIVATABLE_H

class Activatable
{
public:
	Activatable();
	Activatable(const Activatable& a) = delete;
	Activatable& operator=(const Activatable& a) = delete;
	virtual ~Activatable() = default;

protected:
	virtual void OnActivation() = 0;

private: // functions only accessible thru attorney
	friend class ActivatableAttorney;
	void Activate();

private:
	bool isActivated;
};

#endif