from django.urls import path
from . import views

urlpatterns = [
    path('', views.home),
    path('article/<id_article>', views.view_article),
    path('add/<nbr_1>/<nbr_2>', views.add),
]
