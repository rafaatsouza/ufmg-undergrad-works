import argparse
import GraphLib as gl
from git import Repo

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

graphLib = gl.GraphLib()

repo = Repo(args.folder)
repo.git.checkout('master')
commits = repo.iter_commits()

while True:
    try:
        commit = next(commits)
        commitFiles = commit.stats.files
        for file in commitFiles:
            if not file.endswith(args.fileType):
                continue
            for otherFile in commitFiles:
                if file == otherFile:
                    continue
                if not otherFile.endswith(args.fileType):
                    continue
                graphLib.addEdge(file, otherFile)
    except StopIteration:
        break

print('Files most modified together:')
print(graphLib.getHeaviestEdge())
print('Most relationships by file:')
print(graphLib.getMostRelatedNode())
print('Most important file:')
print(graphLib.GetMostImportantFile())