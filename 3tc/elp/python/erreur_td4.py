# Les erreurs dans python

# Les erreurs sont des types dans python
# Ce sont des exceptions : condition d'exécution exceptionnelle

def divide(x, y):
    try:
        res = x / y
    except ZeroDivisionError:
        print("divition by zero !")
    else:
        # S'il n'y a pas d'erreur, on exécute ce bloc
        print("result is", res)
    finally:
        # Bloc exécuté quoiqu'il arrive : si une erreur est attrapée ou pas ou que rien ne se passe mal
        # Fermeture des ressources
        print("finally executed")

divide(3, 4)
# result is 0.75
# finally executed

divide(3, 0)
# Division by zero !
# finally executed

divide("3", "4")
# finally executed
# -------------------------------
# TypeError

# Pour supporter l'erreur précédente
del divide
def divide(x, y):
    try:
        res = x / y
    except ZeroDivisionError:
        print("divition by zero !")
    except TypeError as e:
        print("type error !", e)
    else:
        # S'il n'y a pas d'erreur, on exécute ce bloc
        print("result is", res)
    finally:
        # Bloc exécuté quoiqu'il arrive : si une erreur est attrapée ou pas ou que rien ne se passe mal
        # Fermeture des ressource
        print("finally executed")

divide("3", "4")
# type error ! unsupported operand types
# finally executed

# Définition de son propre type d'erreur
class MyError(Exception):
    pass

if 3 > 2:
    raise MyError("Shit happened !")


# Héritage avec des exceptions
class A(Exception):
    pass
class B(A):
    pass

try:
    raise B("B raised !")
except A:
    print("A caught!")
except B:
    print("B caught!")
# A caught
# A est attrapé en premier car A est dans le premier except
# la clause except B devrait être définie avant except A pour être levée en premier


# Attraper toutes les erreurs
try:
    raise B("spifod")
except:
    print("Smth smth")
