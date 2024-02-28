#pragma once

bool GitIsPopulated();
bool GitAnyUncommittedChanges();
const char* GitAuthorName();
const char* GitAuthorEmail();
const char* GitCommitSHA1();
const char* GitCommitDate();
const char* GitCommitSubject();
const char* GitCommitBody();
const char* GitDescribe();
const char* GitBranch();
const char* GitTagVersion();
const char* GitPatchVersion();
const char* GitBuildVersion();
