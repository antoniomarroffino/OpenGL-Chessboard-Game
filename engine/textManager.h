#pragma once

#include <list>
#include <string>

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

class ENG_API TextManager {
public:
	TextManager(const TextManager&) = delete;
	TextManager& operator=(const TextManager&) = delete;
	~TextManager();

	static TextManager& getInstance();

	void displayText(const std::list<std::string>&) const;

private:
	TextManager();
};

