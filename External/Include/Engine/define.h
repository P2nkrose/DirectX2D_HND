#pragma once


#define SINGLE(Type) private:\
						Type();\
						~Type();\
						friend class qSingleton<Type>;

#define DEVICE qDevice::GetInst()->GetDevice()
#define CONTEXT qDevice::GetInst()->GetContext()

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;