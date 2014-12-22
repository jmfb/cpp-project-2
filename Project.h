#pragma once
#include <string>
#include <vector>

class Project
{
public:
	Project() = default;
	Project(const Project& rhs) = default;
	~Project() = default;

	Project& operator=(const Project& rhs) = default;

	void New(const std::string& directory, const std::string& name);
	void Open(const std::string& fileName);
	void Save();

	const std::string& GetFileName() const;
	const std::string& GetName() const;
	const std::string& GetStandard() const;
	const std::string& GetSubsystem() const;
	const std::string& GetWarnings() const;
	bool GetWarningsAsErrors() const;
	const std::string& GetOptimizationLevel() const;
	const std::string& GetTarget() const;
	const std::string& GetArchitecture() const;
	bool GetDebugInfo() const;
	bool GetMultithreaded() const;
	const std::string& GetOutputFolder() const;
	const std::string& GetOutputFileName() const;
	const std::vector<std::string>& GetIncludeDirectories() const;
	const std::vector<std::string>& GetLibraries() const;
	const std::vector<std::string>& GetProjectReferences() const;

	void SetName(const std::string& value);
	void SetStandard(const std::string& value);
	void SetSubsystem(const std::string& value);
	void SetWarnings(const std::string& value);
	void SetWarningsAsErrors(bool value);
	void SetOptimizationLevel(const std::string& value);
	void SetTarget(const std::string& value);
	void SetArchitecture(const std::string& value);
	void SetDebugInfo(bool value);
	void SetMultithreaded(bool value);
	void SetOutputFolder(const std::string& value);
	void SetOutputFileName(const std::string& value);
	void SetIncludeDirectories(const std::vector<std::string>& value);
	void SetLibraries(const std::vector<std::string>& value);
	void SetProjectReferences(const std::vector<std::string>& value);

private:
	void LoadXml(const std::string& text);
	void LoadJson(const std::string& text);
	std::string ToJson();

private:
	friend class ProjectTest;
	std::string fileName;
	std::string name;
	std::string standard;
	std::string subsystem;
	std::string warnings;
	bool warningsAsErrors = false;
	std::string optimizationLevel;
	std::string target;
	std::string architecture;
	bool debugInfo = false;
	bool multithreaded = false;
	std::string outputFolder;
	std::string outputFileName;
	std::vector<std::string> includeDirectories;
	std::vector<std::string> libraries;
	std::vector<std::string> projectReferences;
};

