State of the Art :
- ConvNet+Deep BeliefNet+Deep Boltzmann Machines: "Deep Learning for Computer Vision: A Brief Review", Voulodimos et al., 2018.
- "Deep Learning", LeCunn et al., 2015.
- Réseau classique orienté économie : "Benchmarking state-of-the-art classification algorithms for credit scoring: A ten-year update", Lessmann et al., 2015.

## Types de réseaux

### Neural Network

- Preprocessing
- Feed forward
- Activation function
- Learning rate
- Loss function
- Backpropagation

### Convolutionnal Neural Network

- Input volume (32x32x3) + X filters (5x5x3) ->
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

### Generative Adversarial Networks

- Un modèle génératif et un modèle discriminant
- Le modèle discriminant cherche à distinguer une vraie donnée d'une donnée générée par le modèle génératif
- G le générateur et D le discriminant, x la data et p_g la data générée, z du bruit pour l'input :
    - On entraine D à maximiser la probabilité D(x) que x appartienne à la data plutôt qu'à p_g
    - On entraine G à minimiser log(1 - D(G(z)))
- D est entrainé k fois, puis G est entrainé : permet de garder D proche de sa solution optimale pendant l'entrainement de G

### Capsule Networks

### Récurrent Neural Network

- "Multiple Object Recognition with Visual Attention", Ba et al.
- "DRAW : A Recurrent Neural Network For Image Generation", Gregor et al.
- "Visualizing and Understanding Recurrent Networks", Andrej Karpathy, Justin Johnson, Li Fei-Fei.
- Image captioning + Selective attention : "Show Attend and Tell", Xu et al., 2015.
- Formule de récurrence : LTSM (Hochreiter et al., 1997)
- Variante de LSTM : "LSTM : A Search Space Odyssey", Greff et al., 2015. "An Empirical Exploration of Recurrent Network Architectures", Jozefowicz et al., 2015. "Learning phrase representations using mn encoder-decoder for statistical machine translation", Cho et al., 2014.

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

ConvNet in Practice :
- Preprocessing : Color jitter : Krizhevsky et al. 2012 (AlexNet)
- Transfer Leanrning : "CNN Features off-the-shelf: an Astounding Baseline for Recognition", Razavian et al., 2014. "DeCAF: A Deep Convolutionnal Activation Feature for Generic Visual Recognition", Donahue, Jia et al., 2013.

Training on large scale database : https://code.fb.com/ml-applications/advancing-state-of-the-art-image-recognition-with-deep-learning-on-hashtags/

Deep Dream :
- Présentation de GoogLeNet : "Going deeper with convolutions", Szegedy et al., 2014.
- "A Neural Algorithm of Artistic Style", Gatys, Ecker, Bethge, 2015.
- "Understanding Neural Networks Through Deep Visualization", Yosinski et al., 2015.

Deep Stereo :
- "DeepStereo: Learning to Predict New Views from the World's Imagery", John Flynn, Ivan Neulander, James Philbin, Noah Snavely, 2015.
