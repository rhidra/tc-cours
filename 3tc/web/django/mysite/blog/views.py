from django.http import HttpResponse
from django.shortcuts import render

def home(request):
    return HttpResponse("""
        <h1>Bienvenue sur mon blog !</h1>
        <p>Les crêpes bretonnes ça tue des mouettes en plein vol !</p>
    """)

def view_article(request, id_article):
    return HttpResponse("Voici l'article n°#{0} !".format(id_article))

def add(request, nbr_1, nbr_2):
    total = nbr_1 + nbr_2
    return render(request, 'blog/add.html', locals())
