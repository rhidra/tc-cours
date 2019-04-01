State of the Art :
- ConvNet+Deep BeliefNet+Deep Boltzmann Machines: "Deep Learning for Computer Vision: A Brief Review", Voulodimos et al., 2018.
- "Deep Learning", LeCunn et al., 2015.
- Réseau classique orienté économie : "Benchmarking state-of-the-art classification algorithms for credit scoring: A ten-year update", Lessmann et al., 2015.

## Types de réseaux

### Artificial Neural Network

- Data Preprocessing :
    - Zero centered : soustrait la moyenne des pixels
    - Zero centered by channel : soustrait la moyenne de chaque canal de pixels
    - Normalization : Not common sur des images
- Feed forward
- Activation function : Améliore la stimulation du neurone lorsqu'il trouve quelque chose qui lui plaît
                        Sans AF : NN équivalent à un classifieur linéaire
    - Sigmoid / tanh : obsolètes car elles tuent le gradient, et non-zero centered
    - ReLU = `max(0, x)` : standard, mais sature dans les négatifs
    - Leaky ReLU = `max(0.1x, x)` ou `max(alpha*x, x)` avec alpha paramètre du NN
    - Maxout = `max(W_1*x, W_2*x)`: Généralisation de ReLU, mais double le nombre de paramètre
    - ELU
- Loss function :
    - Hinge-loss / SVM : `L_i = SUM[ max(0, s_j - s_y_i + 1), j!=y_i ]`
                         `L = (1/N) * SUM[ L_i, i=1..N ]`
    - cross-entropy / softmax : softmax(s, i) = exp(s_i) / SUM[ exp(s_k), k=0..K ] avec s={s_0, ..., s_K}
      Permet de transformer un vecteur de score en un vecteur de probabilités
      L_i = - log(softmax(s, i))
- Regularization :
    - Loss = L + Lambda*R(W)
    - R(W) permet d'avoir des propriétés intéressantes sur W
    - L2 Regularization (W préféré lorsque proche de 0, permet d'étaler W sur les dimensions et d'utiliser toutes les propriétés de l'image) : SUM[ SUM[ W_k_l², k ], l ]
    - L1
    - Max norm Regularization : seuil sur la norme des coefficients
- Backpropagation
    - Chain rule
- Parameters Update (Learning rate) :
    - SGD : Stochastic Gradient Descent (W = W - learning_rate * grad)
    - Momentum : `x = (v = mu*v - learning_rate*dx)` : Interprétation physique de l'accélératio (mu = friction)
    - Nesterov-SGD
    - AdaGrad + RMSProp : Chaque paramètre a son propre learning rate
                        cache = decay_rate * cache + (1-decay_rate) * dx
                        x += - learning_rate * dx / (sqrt(cache) + 1e-7)
    - Adam : Mélange entre RMSProp et Momentum
    - Second order optimization : Permet d'éviter d'avoir un learning rate, mais nécessite plus de calculs
        - Quasi-Newton method : BGFS
        - L-BGFS : Limited Memory BGFS, efficace avec peu de data
- Dropout :
    - A chaque Forward pass, on génère un masque binaire pour éliminer des neurones aléatoirement
    - Doit être fait à la forward et la backward pass
    - Pdt test, il faut multiplier après l'AF par la proba du masque (`p=0.5`)
    - Inverted dropout : On divise le masque par `p` pour laisser le test non changé
- Mini-batch gradient descent :
    - Lors de l'optimization, on optimise d'abord sur des petits échantillons différents des training data, pour approximer le gradient mais aller plus vite
- Initialisation des weights :
    - Surtout pas à zéro !
    - Random de petits nombres (`0.01*rand()`) : OK pour de petits réseaux
    - Xavier Initialisation : Mieux mais ne fonctionne pas avec un AF non-linéaire (ReLU) sans  un facteur de 2 [Glorot et al., 2010] [He et al., 2015]
    - Data driven initialisation (cf. stacked autoencoder)
- Batch Normalization :
    - Normalisation du batch sur les features
    - S'insère entre les FC layers, avec l'AF
    - Après la normalisation, on shift toute la data linéairement avec des paramètres sur lesquels on backprop : `y=a*norm(x)+n`

### Convolutionnal Neural Network

- Input volume (32x32x3) + 6 filters (5x5x3) ->  28x28x6
- Stride ("Vitesse" de déplacement dans la convolution)
- Padding
- Pooling layer : Downsampling des layers (layer 224x224x64 -> 112x112x64)
-- Max pooling : on prend le max d'une certaine région
-- Average pooling : moyenne au lieu du max
- FC (Fully Connected Layer) : Neural network classique qui prend l'output final et classifie

Pour limiter le nombre de paramètres à entrainer :
- Dropout
- Batch normalization
- Data augmentation

- AlexNet : "ImageNet Classification with Deep Convolutional Neural Network", Krizhevsky et al., 2012.
- VGGNet : "Very Deep Convolutional Networks for Large Scale Image Recognition", Simonyan, Zisserman, 2015.
- GoogLeNet : "Going deeper with convolutions", Szegedy et al., 2014.
- ResNet : "Deep Residual Learning for Image Recognition", He et al., 2015.
- Inception V4 (Inception-ResNet)
- Squeeze and Excitation module
- Progressive Neural Architecture Search

### Deep Belief Networks (DBN) & Deep Boltzmann Machines (DBM)

- Based on the Restricted Boltzmann Machines (RBM)
    - Undirected graphical model
    - Stochastic visible (v) and hidden (h) variable, each v is connected to each h (bipartite graph)
    - Fonction énergie (E) qui donne l'état préférentiel du système à son minimum
    - A partir de exp(-E) on déduit la probabilité d'un état du système
- Deep Belief Networks (DBN)
    - Stack de RBM
    - l hidden layer (h^k) donc DBN = [h⁰, h¹, h², ... h^(l), v] avec l'input x = h⁰
    - L'output v est déterminé de manière probabiliste

### Stacked Autoencoders

- Autoencoder : Single layer NN où l'objectif est d'obtenir l'output le plus similaire à l'input possible
- Stacked AE : plusieurs hidden layers
- On peut ajouter du bruit à un input : permet de denoiser une image
- Le training est différent d'un NN :
    - On envoie un input noisé dans l'AE
    - La loss function compare l'output avec l'input attendu
    - On continue jusqu'à la convergence des coefficients
    - Le nouvel input est alors le contenu des hidden layers
- Applications :
    - Système de compression d'image
    - Apprentissage non supervisé
    - On réutilise les coefs entrainés de l'AE dans un deep NN => Mieux que d'initialisé de façon aléatoire
    - Denoiser

### Capsule Networks

- Compense les problèmes des CNNs :
    - Ne prend pas en compte les relations de translations et de rotations entre les neurones inférieurs et supérieurs
      dans une convolution
    - La solution est généralement les layers de pooling en augmentant le FOV des niveaux supérieurs
- Le cerveau analyse une image et en reconstruit la structure et la géométrie de chaque élément
  Donc sa compréhension d'une image ne dépend pas de l'angle de vue d'un objet, juste de sa structure.
  CapsNet reprend ce concept.
- Les capsules encodent la probabilité de détection d'une caractéristiques par la longueur d'un vecteur
  et son état par la direction du vecteur.
  Donc quand une feature se déplace sur l'image, la direction du vecteur change, mais pas sa longueur => invariance !
- Capsule j :
    - Input U1 = vecteur qui représente la proba + position d'une feature profonde (position/proba du nez)
    - Multiplication par matrice W1j = W1j représente la relation entre la position/proba du nez et la tête.
      Après multiplication, on a Û1 qui représente la position/proba de la tête en fonction de la pos/proba du nez
      Il faut encore mettre en relation Û1 avec Û2 (position de la tête par rapport à la bouche), Û3 (par rapport aux yeux), etc.
    - Multiplication scalaire à un poids C1 qui détermine l'importance du vecteur Û1 dans le calcul de la sortie de la capsule j.
      Càd la proba que les informations sur un nez soient importantes pour déterminer une tête.
      C1 est calculé par un algo de dynamic routing, pas par de la backpropagation !
    - Somme de tous les inputs coefficientés, similaire à un neurone classique
    - Fonction de squash non-linéaire
- Dynamic routing :
    - Algo pour estimer Cij en fonction de Ûij
    - On calcule d'abord Vj la somme de tous les inputs coefficientés avec des Wij et des Cij initialisés
    - La nouvelle valeur de Cij est le produit scalaire entre Vj et Ûij, soit une mesure de la similarité entre l'entrée et la sortie.
    - On itère cet algo 3 fois
- https://medium.com/ai%C2%B3-theory-practice-business/understanding-hintons-capsule-networks-part-ii-how-capsules-work-153b6ade9f66

### Récurrent Neural Network

- Plusieurs configurations :
    - one to one (vanillla)
    - one to many (image captioning)
    - many to one (sentiment analysis)
    - many to many unsynchronised (translation)
    - many to many synchronised (video analysis)
- State du réseau h :
    - `h = tanh(W_hh * h + W_xh * x)`
    - `y = W_hy * h`
    - `W_hh` : Matrice basée sur l'état précédent
    - `W_xh` : Matrice basée sur l'input actuel
    - `W_hy` : Matrice basée sur un mélange entre l'input et l'état du RNN
    - `h` : vecteur d'état du RNN, initialisé à 0
- Pour ajouter des couches :
    - On empile les RNNs
    - Ou LSTM
- LSTM : on sélectionne grâce à des gates ce qu'on oublie ou rajoute dans un cell state `C`
    - State vectors : `h_t` et `C_t`
    - `f_t = sigm(W_f * [h_t-1, x_t] + b_f)` : gate d'oublie (forget)
    - `i_t = sigm(W_i * [h_t-1, x_t] + b_i)` : gate d'ajout (input)
    - `~C_t = tanh(W_C * [h_t-1, x_t] + b_C)` : ce qu'on ajoute
    - `C_t = f_t * C_t-1 + i_t * ~C_t` : mise à jour de `C_t`
    - `o_t = sigm(W_o * [h_t-1, x_t] + b_o)` : gate de ce qu'on garde pour la suite (output)
    - `h_t = o_t * tanh(C_t)` : mise à jour de `h_t`
- Il existe plusieurs variantes de LSTM :
    - Peephole connections (Gers & Schmidhuber, 2000)
    - Coupled forget and input gates (On oublie uniquement si on remplace par un input)
    - GRU (Gated Recurrent Unit) (Cho, et al, 2014)

- "Multiple Object Recognition with Visual Attention", Ba et al.
- "DRAW : A Recurrent Neural Network For Image Generation", Gregor et al.
- "The Unreasonable Effectiveness of Recurrent Neural Networks", Andrej Karpathy.
- "Visualizing and Understanding Recurrent Networks", Andrej Karpathy, Justin Johnson, Li Fei-Fei.
- "Image captioning + Selective attention : "Show Attend and Tell", Xu et al., 2015.
- Formule de récurrence : LTSM (Hochreiter et al., 1997)
- Variante de LSTM : "LSTM : A Search Space Odyssey", Greff et al., 2015. "An Empirical Exploration of Recurrent Network Architectures", Jozefowicz et al., 2015. "Learning phrase representations using mn encoder-decoder for statistical machine translation", Cho et al., 2014.

### Neuroévolution

- Applications de d'algo génétiques pour entrainer un NN
- Alternative à la gradient descent et à la backpropagation
- Utile pour des tâches de Reinforcement Learning (jouer à des jeux-vidéos)
- Mais pas utile pour de l'image

## Techniques de Computer Vision

Localization (Régression) :

- Conv net + 2*FC pour classe et localisation
- Sliding window : Overfeat
- ResNet : (RPN method)

Détection :
Problem : output size variable

- Classification à travers pleins de morceaux de l'image
- Deformable Parts Models optimisation ("Deformable Part Models are Convolutional Neural Networks")
- Optimisation par isolation de zones de recherche préférentielles : (ex: Algo Selective Search) ("What makes for effective detection proposals?")

## Applications

### Generative Adversarial Networks

- Un modèle génératif et un modèle discriminant
- Le modèle discriminant cherche à distinguer une vraie donnée d'une donnée générée par le modèle génératif
- G le générateur et D le discriminant, x la data et p_g la data générée, z du bruit pour l'input :
- On entraine D à maximiser la probabilité D(x) que x appartienne à la data plutôt qu'à p_g
- On entraine G à minimiser log(1 - D(G(z)))
- D est entrainé k fois, puis G est entrainé : permet de garder D proche de sa solution optimale pendant l'entrainement de G

- Génération de visage HD : "Progressive Growing of GANs for Improved Quality, Stability and Variation", Karras et al., 2018.
- Moteur graphique : "Video-to-Video Synthesis", Wang et al., 2018.

### ConvNet in Practice
- Preprocessing : Color jitter : Krizhevsky et al. 2012 (AlexNet)
- Transfer Leanrning : "CNN Features off-the-shelf: an Astounding Baseline for Recognition", Razavian et al., 2014. "DeCAF: A Deep Convolutionnal Activation Feature for Generic Visual Recognition", Donahue, Jia et al., 2013.

Training on large scale database : https://code.fb.com/ml-applications/advancing-state-of-the-art-image-recognition-with-deep-learning-on-hashtags/

### RNN with video
- Video classification : "Beyond short snippets: Deep networks for video classification", Ng et al., 2015.
- Object tracking : "Learning a deep compact image representation for visual tracking", Wang et al., 2013.
- Object tracking : "Spatially Supervised Recurrent Convolutional Networks for Visual Object Tracking", Ning et al., 2016.
- Speech reconstruction : "Vid2speech: Speech Reconstruction from Silent Video", Ephrat et al., 2017.
- Lip reading : "LipNet: Sentence-level Lipreading", Assael et al., 2016.
- Lip reading : "Lip reading sentences in the wild", Chung et al., 2016.

### Deep Dream / Deep Style
- Présentation de GoogLeNet : "Going deeper with convolutions", Szegedy et al., 2014.
- "A Neural Algorithm of Artistic Style", Gatys, Ecker, Bethge, 2015.
- "Understanding Neural Networks Through Deep Visualization", Yosinski et al., 2015.

### Deep Stereo
- "DeepStereo: Learning to Predict New Views from the World's Imagery", John Flynn, Ivan Neulander, James Philbin, Noah Snavely, 2015.
