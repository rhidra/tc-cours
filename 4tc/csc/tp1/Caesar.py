##############################################################
# This file is adapted from laboratory exercises given in
# the "Understanding Cryptology: Cryptanalysis" course offered
# by Dr. Kerry McKay
# Hosted at OpenSecurityTraining.info under a CC BY-SA license
# http://creativecommons.org/licenses/by-sa/3.0/
##############################################################

# objective: find the plaintext of "ciphertext"

alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m',
            'n','o','p','q','r','s','t','u','v','w','x','y','z']

english = {'a':8.167,'b':1.492,'c':2.782,'d':4.253,'e':12.702,'f':2.228,
           'g':2.015,'h':6.094,'i':6.966,'j':0.153,'k':0.772,'l':4.025,'m':2.406,
           'n':6.749,'o':7.507,'p':1.929,'q':0.095,'r':5.987,'s':6.327,'t':9.056,
           'u':2.758,'v':0.978,'w':2.36,'x':0.15,'y':1.974,'z':0.074}

ciphertext = "di xmtkojbmvkct  v xvznvm xdkczm  vgnj fijri vn xvznvm n xdkczm ocz ncdao xdkczm  xvznvm n \
xjyz jm xvznvm ncdao  dn jiz ja ocz ndhkgzno viy hjno rdyzgt fijri zixmtkodji ozxcidlpzn do dn v otkz ja npwnodopodji \
xdkczm di rcdxc zvxc gzoozm di ocz kgvdiozso dn mzkgvxzy wt v gzoozm njhz adszy iphwzm ja kjndodjin yjri ocz vgkcvwzo \
ocz xvznvm xdkczm dn zvndgt wmjfzi viy di hjyzmi kmvxodxz jaazmn znnziodvggt ij xjhhpidxvodji nzxpmdot \
ocz amzlpzixt ja gzoozmn di ozso cvn jaozi wzzi nopydzy ajm pnz di xmtkojbmvkct viy amzlpzixt vivgtndn di kvmodxpgvm\
hjmz mzxzio vivgtnzn ncjr ocvo gzoozm amzlpzixdzn gdfz rjmy amzlpzixdzn oziy oj qvmt wjoc wt rmdozm viy wt npwezxo \
ocz lpdxf wmjri ajs ephkn jqzm ocz gvut yjb"

def listToString(myList):
    return ''.join(myList)

###################
# Encrypt a string
# inputs:
#   p - string to encrypt
#   k - a number 0 through 25 that is the key
###################

def encrypt(p, k):
    c = []
    for i in range(len(p)):
        if p[i] == " ":
            c.append(" ")
        else:
            index = alphabet.index(p[i])
            c.append(alphabet[(index+k)%26])

    return listToString(c)

###################
# Decrypt a string
# inputs:
#   c -  string to decrypt
#   k - a number 0 through 25 that is the key
###################
def decrypt(c, k):
    p = []
    for i in range(len(c)):
        if c[i] == " ":
            p.append(" ")
        else:
            index = alphabet.index(c[i])
            p.append(alphabet[(index-k)%26])
    return listToString(p)


###################
# Create relative frequency list based on a string
# inputs:
#   data - string to compute relative frequencies on
###################
def relativeFrequency(data):
    #store the frequency of each letter in a dictionary
    freq = dict()
    for i in range(len(data)):
        if data[i]!=" ":
            if data[i] in freq:
                freq[data[i]]=freq[data[i]]+1
            else:
                freq[data[i]]=1
    n=sum(freq.values())
    for key in freq.keys():
        freq[key]=freq[key]*100/n

    return freq

def BruteForce(data):
    for i in range(1,1000):
        d = decrypt(data, i)
        print(d)
        input('Pour i = {}'.format(i))

def FrequencyAnalysis(data):
    r = relativeFrequency(data)
    sortedEnglish = sorted(english, key=lambda key: english[key])
    sortedFrequencies = sorted(r, key=lambda key: r[key])

    print ("english\t\t ciphertext")
    for i in range(len(sortedFrequencies)-1, 0 ,-1):
        print ("{0}\t\t{1}".format(sortedEnglish[i],sortedFrequencies[i]))
