#pragma once

// Generic info:
// Export API:
#ifdef _WINDOWS
   // Specifies i/o linkage (VC++ spec):
#ifdef ENGINE_EXPORTS
#define ENG_API __declspec(dllexport)
#else
#define ENG_API __declspec(dllimport)
#endif

// Get rid of annoying warnings:
#pragma warning(disable : 4251)
#else // Under linux
#define ENG_API
#endif

class ENG_API ChangeMatrixListener {
public:
	virtual ~ChangeMatrixListener() = default;
	virtual void onMatrixChange(const unsigned int&) = 0;
};