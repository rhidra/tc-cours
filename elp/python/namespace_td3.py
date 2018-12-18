# Namespaces

# Namespace = maping identifiant <=> objet

# Scope = zone textuelle (dans une fonction/module/...)
# Dans une fonction, 4 scopes :
# - local
# - non-local = fonctions englobante => peut-être plusieurs fonctions
# - global = module
# - built-ins
# Quand on accède à une variable, python recherche la variable dans le scope dans cet ordre

def scope_test():
    def do_local():
        name = "local name"
    def do_nonlocal():
        # On déclare que name (On le crée aussi) est une variable non locale
        nonlocal name
        name = "nonlocal name"
    def do_global():
        # Le global est à l'extèrieur de la fonction, donc on va modifier name à l'extèrieur du scope de la fonction
        global name
        name = "global test"
    name = "test name"
    do_local()
    print("after local assignement:", name)
    do_nonlocal()
    print("after nonlocal assignement:", name)
    do_global()
    print("after global assignement:", name)

scope_test()
# after local: test name
# after nonlocal: nonlocal name
# after global: nonlocal name
name # Affiche "global test" car name est créé dans le scope global du module
