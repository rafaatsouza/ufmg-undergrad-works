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

#1. Quantos commits possui o projeto? 
if args.option == "1":
	gitPyService.GetTotalCommits()

#2. Quantos commits foram realizados em 2019? Em 2018? Em 2017 
elif args.option == "2":
	gitPyService.GetTotalCommits(args.yearFrom, args.yearTo)

#3. Quantos commits incluem a string “feature”? E a string “fix”? 
elif args.option == "3":
	gitPyService.GetTotalCommits(message=args.searchString)

#4. Quais os 5 arquivos <extensao> mais modificados? 
#5. Quais os 5 arquivos <extensao> mais modificados desde 2018? 
#6. Quais os 5 arquivos <extensao> mais modificados em 2017? 
elif args.option == "4" or args.option == "5" or args.option == "6":
	print ("This might take a while if the selected repository has a big number of commits")
	gitPyService.GetMostModifiedFiles(args.yearFrom, args.yearTo, args.fileType, int(args.count))

#7. Quais os 3 desenvolvedores mais ativos? 
# Obs: Serão printados por default os top10, pois o repositório de exemplo tem múltiplos committers que são o mesmo usuário
elif args.option == "7":
	gitPyService.GetTopCommiters(max=int(args.count))

#8. Quais 3 desenvolvedores mais ativos em 2019? 
elif args.option == "8":
	gitPyService.GetTopCommiters(args.yearFrom, args.yearTo, int(args.count))

#9. Quantas vezes List foi adicionado no código? 
elif args.option == "9":
	gitPyService.GetNumberOfEdits(True, args.searchString)

#10. Quantas vezes Dictionary foi removido do código? 
elif args.option == "10":
	gitPyService.GetNumberOfEdits(False, args.searchString)

elif args.option == "11":
	gitPyService.Test()