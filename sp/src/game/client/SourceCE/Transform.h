
#include "Component.h"

class Transform : public Component
{
private:
	Vector localOrigin;
	QAngle localRotation;
	Vector localScale;

	Vector absOrigin;
	QAngle absRotation;
	
	
public:
	Transform* parent;
public:
	Transform* GetRoot() const;
	
};