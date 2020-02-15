import argparse
import GitPyService as gps
import ComplexCalc as cc
from git import Repo
import io
import os
from datetime import datetime as dt
from dateutil.relativedelta import relativedelta as delta
import time

def GetYearAgoCommit(commits):
    yearAgo = (dt.now() - delta(years=1)).strftime('%Y-%m')
    while True:
        commit = next(commits)
        dateTime = time.strftime("%Y-%m", time.gmtime(commit.committed_date))
        if yearAgo == dateTime or yearAgo > dateTime:
            break
    return commit

def GetCommitDateTime(element):
		return time.strftime("%Y-%m-%d", time.gmtime(element.committed_date))

parser = argparse.ArgumentParser(description="Arguments Description")
parser.add_argument('--repo', nargs='?', default='https://github.com/takenet/lime-csharp', help='Repo to use')
parser.add_argument('--folder', nargs='?', default='', help='Folder to use')
parser.add_argument('--option', nargs='?', default=1, help='Option selected from list')
parser.add_argument('--yearTo', nargs='?', default="2019", help='Year to check up to')
parser.add_argument('--yearFrom', nargs='?', default="1969", help='Year to check from')
parser.add_argument('--searchString', nargs='?', default=1, help='String to search for')
parser.add_argument('--count', nargs='?', default=10, help='Positions returned')
parser.add_argument('--fileType', nargs='?', default='.cs', help='File extension to search for')

args = parser.parse_args()

gitPyService = gps.GitPyService(args.folder, args.repo)
complexCalc = cc.ComplexCalc()

# complexidade por indent dos arquivos do ultimo commit
if args.option == "1":
    repo = Repo(args.folder)
    repo.git.checkout('master')
    commits = repo.iter_commits()
    commit = next(commits)
    gitPyService.GetCommitedComplexityMetrics(commit, args.folder, args.fileType)

# complexidade por indent dos arquivos 1 ano atrás
elif args.option == "2":
    repo = Repo(args.folder)
    repo.git.checkout('master')
    commits = repo.iter_commits()
    yearAgo = (dt.now() - delta(years=1)).strftime('%Y-%m')
    commit = GetYearAgoCommit(commits)
    print('At time of commit', commit, '(', GetCommitDateTime(commit) ,')')
    gitPyService.GetCommitedComplexityMetrics(commit, args.folder, args.fileType)

# compleixdade do projeto no ultimo commit
elif args.option == "3":
    repo = Repo(args.folder)
    repo.git.checkout('master')
    commits = repo.iter_commits()
    commit = next(commits)
    repo.git.checkout(commit)
    cp = complexCalc.GetCPByIndent(args.folder, args.fileType)
    print('CP At time of commit', commit, '(', GetCommitDateTime(commit) ,')')
    print(cp)

# compleixdade do projeto 1 ano atras
elif args.option == "4":
    repo = Repo(args.folder)
    repo.git.checkout('master')
    commits = repo.iter_commits()
    commit = GetYearAgoCommit(commits)
    repo.git.checkout(commit)
    cp = complexCalc.GetCPByIndent(args.folder, args.fileType)
    print('CP At time of commit', commit, '(', GetCommitDateTime(commit) ,')')
    print(cp)

# compleixdade do projeto em cada commit
elif args.option == "5":
    repo = Repo(args.folder)
    repo.git.checkout('master')
    commits = repo.iter_commits()
    print('Calculating CP per commit.... takes a long time')
    cpDict = {}
    while True:
        try:
            commit = next(commits)
            repo.git.checkout(commit)
            cp = complexCalc.GetCPByIndent(args.folder, args.fileType)
            cpDict[commit] = cp
        except StopIteration:
            break
    print('CP Dictionary:')
    print(cpDict)