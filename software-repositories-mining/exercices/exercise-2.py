import argparse
import GitPyService as gps

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

# qtd de arquivos no primeiro e ultimo commits
if args.option == "1":
    gitPyService.GetCountFilesFirstAndLastCommits(args.folder)

# qtd de arquivos da extensao no primeiro e ultimo commits
elif args.option == "2":
    gitPyService.GetCountFilesFirstAndLastCommits(args.folder, args.fileType)

# qtd de arquivos em cada commit
elif args.option == "3":
    gitPyService.GetCountFilesByCommit(args.folder)

# qtd de arquivos da extensao em cada commit
elif args.option == "4":
    gitPyService.GetCountFilesByCommit(args.folder, args.fileType)

# numero de linha de codigo da extensao em cada commit
elif args.option == "5":
    gitPyService.GetLinesByFile(folderPath=args.folder, fileType=args.fileType)

# qtd de arquivos por ano
elif args.option == "6":
    gitPyService.GetCountFilesByYear(args.folder)

# qtd de arquivos da extensao por ano
elif args.option == "7":
    gitPyService.GetCountFilesByYear(folderPath=args.folder, fileType=args.fileType)

# numero de linhas de codigo da extensao por ano
elif args.option == "8":
    gitPyService.GetCommitedFilesByYear(folderPath=args.folder, fileType=args.fileType)

elif args.option == "9":
    gitPyService.GetAllFilesByYear(folderPath=args.folder, fileType=args.fileType)
