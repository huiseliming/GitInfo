#pragma once
#include "GitInfo.api.h"

GITINFO_API bool GitIsDirty();
GITINFO_API const char *GitCommitSHA1();
GITINFO_API const char *GitCommitDate();
GITINFO_API const char *GitDescribe();
GITINFO_API const char *GitTagVersion();
GITINFO_API const char *GitPatchVerison();
GITINFO_API const char *GitBuildVersion();
