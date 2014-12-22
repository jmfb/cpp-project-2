#include <Wex/WindowsInclude.h>
#include "Project.h"
#include <fstream>
#include <cstring>
#include <Wex/Path.h>
#include <Wex/File.h>
#include <Wex/Directory.h>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "json/value.h"
#include "json/reader.h"
#include "json/writer.h"

const auto defaultName = "Project1";
const auto defaultStandard = "c++11";
const auto defaultSubsystem = "windows";
const auto defaultWarnings = "all";
const auto defaultWarningsAsErrors = true;
const auto defaultOptimizationLevel = "4";
const auto defaultTarget = "EXE";
const auto defaultArchitecture = "32-bit";
const auto defaultDebugInfo = false;
const auto defaultMultithreaded = true;
const auto defaultOutputFolder = "output";
const auto defaultOutputFileName = "{ProjectName}.exe";

void Project::New(const std::string& directory, const std::string& name)
{
	auto projectDirectory = Wex::Path::Combine(directory, name);
	fileName = Wex::Path::Combine(projectDirectory, name + ".cpp-project");
	this->name = name;
	standard = defaultStandard;
	subsystem = defaultSubsystem;
	warnings = defaultWarnings;
	warningsAsErrors = defaultWarningsAsErrors;
	optimizationLevel = defaultOptimizationLevel;
	target = defaultTarget;
	architecture = defaultArchitecture;
	debugInfo = defaultDebugInfo;
	multithreaded = defaultMultithreaded;
	outputFolder = defaultOutputFolder;
	outputFileName = defaultOutputFileName;
	includeDirectories.clear();
	libraries.clear();
	projectReferences.clear();
}

void Project::Open(const std::string& fileName)
{
	this->fileName = fileName;

	auto text = Wex::File::ReadAllText(fileName);
	if (text.empty())
		return;
	if (text[0] == '<')
	{
		Wex::File::CopyOver(fileName, fileName + ".xml");
		LoadXml(text);
		Save();
	}
	else
		LoadJson(text);
}

void Project::Save()
{
	auto projectDirectory = Wex::Path::GetPath(fileName);
	Wex::Directory::Create(projectDirectory);
	std::ofstream out(fileName.c_str());
	out << ToJson();
}

const std::string& Project::GetFileName() const
{
	return fileName;
}

const std::string& Project::GetName() const
{
	return name;
}

const std::string& Project::GetStandard() const
{
	return standard;
}

const std::string& Project::GetSubsystem() const
{
	return subsystem;
}

const std::string& Project::GetWarnings() const
{
	return warnings;
}

bool Project::GetWarningsAsErrors() const
{
	return warningsAsErrors;
}

const std::string& Project::GetOptimizationLevel() const
{
	return optimizationLevel;
}

const std::string& Project::GetTarget() const
{
	return target;
}

const std::string& Project::GetArchitecture() const
{
	return architecture;
}

bool Project::GetDebugInfo() const
{
	return debugInfo;
}

bool Project::GetMultithreaded() const
{
	return multithreaded;
}

const std::string& Project::GetOutputFolder() const
{
	return outputFolder;
}

const std::string& Project::GetOutputFileName() const
{
	return outputFileName;
}

const std::vector<std::string>& Project::GetIncludeDirectories() const
{
	return includeDirectories;
}

const std::vector<std::string>& Project::GetLibraries() const
{
	return libraries;
}

const std::vector<std::string>& Project::GetProjectReferences() const
{
	return projectReferences;
}

void Project::SetName(const std::string& value)
{
	name = value;
}

void Project::SetStandard(const std::string& value)
{
	standard = value;
}

void Project::SetSubsystem(const std::string& value)
{
	subsystem = value;
}

void Project::SetWarnings(const std::string& value)
{
	warnings = value;
}

void Project::SetWarningsAsErrors(bool value)
{
	warningsAsErrors = value;
}

void Project::SetOptimizationLevel(const std::string& value)
{
	optimizationLevel = value;
}

void Project::SetTarget(const std::string& value)
{
	target = value;
}

void Project::SetArchitecture(const std::string& value)
{
	architecture = value;
}

void Project::SetDebugInfo(bool value)
{
	debugInfo = value;
}

void Project::SetMultithreaded(bool value)
{
	multithreaded = value;
}

void Project::SetOutputFolder(const std::string& value)
{
	outputFolder = value;
}

void Project::SetOutputFileName(const std::string& value)
{
	outputFileName = value;
}

void Project::SetIncludeDirectories(const std::vector<std::string>& value)
{
	includeDirectories = value;
}

void Project::SetLibraries(const std::vector<std::string>& value)
{
	libraries = value;
}

void Project::SetProjectReferences(const std::vector<std::string>& value)
{
	projectReferences = value;
}

void Project::LoadXml(const std::string& text)
{
	const auto xmlBoolTrue = "True";
	const auto xmlBoolFalse = "False";

	rapidxml::xml_document<char> document;
	document.parse<0>(const_cast<char*>(text.c_str()));

	auto project = document.first_node("Project");

	auto nameAttribute = project ? project->first_attribute("name") : nullptr;
	name = nameAttribute ? nameAttribute->value() : defaultName;

	auto settings = project ? project->first_node("Settings") : nullptr;

	auto loadSetting = [&](const char* nodeName, const char* defaultValue) -> const char*
	{
		auto node = settings ? settings->first_node(nodeName) : nullptr;
		return node ? node->value() : defaultValue;
	};
	auto loadBitSetting = [&](const char* nodeName, bool defaultValue) -> bool
	{
		return std::strcmp(loadSetting(nodeName, defaultValue ? xmlBoolTrue : xmlBoolFalse), xmlBoolTrue) == 0;
	};

	standard = loadSetting("Standard", defaultStandard);
	subsystem = loadSetting("Subsystem", defaultSubsystem);
	warnings = loadSetting("Warnings", defaultWarnings);
	warningsAsErrors = loadBitSetting("WarningsAsErrors", defaultWarningsAsErrors);
	optimizationLevel = loadSetting("OptimizationLevel", defaultOptimizationLevel);
	target = loadSetting("Target", defaultTarget);
	architecture = loadSetting("Architecture", defaultArchitecture);
	debugInfo = loadBitSetting("DebugInfo", defaultDebugInfo);
	multithreaded = loadBitSetting("Multithreaded", defaultMultithreaded);
	outputFolder = loadSetting("OutputFolder", defaultOutputFolder);
	outputFileName = loadSetting("OutputFileName", defaultOutputFileName);

	auto includeDirectoriesNode = settings ? settings->first_node("IncludeDirectories") : nullptr;
	includeDirectories.clear();
	if (includeDirectoriesNode)
		for (auto node = includeDirectoriesNode->first_node("IncludeDirectory"); node; node = node->next_sibling("IncludeDirectory"))
			includeDirectories.push_back(node->value());

	auto librariesNode = settings ? settings->first_node("Libraries") : nullptr;
	libraries.clear();
	if (librariesNode)
		for (auto node = librariesNode->first_node("Library"); node; node = node->next_sibling("Library"))
			libraries.push_back(node->value());

	auto projectReferencesNode = settings ? settings->first_node("ProjectReferences") : nullptr;
	projectReferences.clear();
	if (projectReferencesNode)
		for (auto node = projectReferencesNode->first_node("ProjectReference"); node; node = node->next_sibling("ProjectReference"))
			projectReferences.push_back(node->value());
}

void Project::LoadJson(const std::string& text)
{
	Json::Value project;
	Json::Reader reader;
	reader.parse(text, project);

	auto loadSetting = [&](
		const char* settingName,
		const char* defaultValue) -> std::string
	{
		auto value = project[settingName];
		return value.isNull() ? defaultValue : value.asString();
	};
	auto loadBitSetting = [&](
		const char* settingName, bool defaultValue) -> bool
	{
		auto value = project[settingName];
		return value.isNull() ? defaultValue : value.asBool();
	};

	name = loadSetting("name", defaultName);
	standard = loadSetting("standard", defaultStandard);
	subsystem = loadSetting("subsystem", defaultSubsystem);
	warnings = loadSetting("warnings", defaultWarnings);
	warningsAsErrors = loadBitSetting("warningsAsErrors", defaultWarningsAsErrors);
	optimizationLevel = loadSetting("optimizationLevel", defaultOptimizationLevel);
	target = loadSetting("target", defaultTarget);
	architecture = loadSetting("architecture", defaultArchitecture);
	debugInfo = loadBitSetting("debugInfo", defaultDebugInfo);
	multithreaded = loadBitSetting("multithreaded", defaultMultithreaded);
	outputFolder = loadSetting("outputFolder", defaultOutputFolder);
	outputFileName = loadSetting("outputFileName", defaultOutputFileName);

	includeDirectories.clear();
	for (const auto& includeDirectory : project["includeDirectories"])
		includeDirectories.push_back(includeDirectory.asString());

	libraries.clear();
	for (const auto& library : project["libraries"])
		libraries.push_back(library.asString());

	projectReferences.clear();
	for (const auto& projectReference : project["projectReferences"])
		projectReferences.push_back(projectReference.asString());
}

std::string Project::ToJson()
{
	Json::Value project(Json::objectValue);
	project["name"] = name;
	project["standard"] = standard;
	project["subsystem"] = subsystem;
	project["warnings"] = warnings;
	project["warningsAsErrors"] = warningsAsErrors;
	project["optimizationLevel"] = optimizationLevel;
	project["target"] = target;
	project["architecture"] = architecture;
	project["debugInfo"] = debugInfo;
	project["multithreaded"] = multithreaded;
	project["outputFolder"] = outputFolder;
	project["outputFileName"] = outputFileName;

	Json::Value jsonIncludeDirectories(Json::arrayValue);
	for (const auto& includeDirectory : includeDirectories)
		jsonIncludeDirectories.append(includeDirectory);
	project["includeDirectories"] = jsonIncludeDirectories;

	Json::Value jsonLibraries(Json::arrayValue);
	for (const auto& library : libraries)
		jsonLibraries.append(library);
	project["libraries"] = jsonLibraries;

	Json::Value jsonProjectReferences(Json::arrayValue);
	for (const auto& projectReference : projectReferences)
		jsonProjectReferences.append(projectReference);
	project["projectReferences"] = jsonProjectReferences;

	Json::StyledWriter writer;
	return writer.write(project);
}

