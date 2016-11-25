1/ Créer tous les dossiers des VM
2/ Dans chaque, copier le Vagrantfile dans lequel on nomme toutes les interfaces de connexion (LAN1, LAN2, ...)
3/ Mettre chaque fichier de config dans la VM :
	 shell: nmcli connection del "Connexion filaire 1 // Pour supprimer les connexions automatiquement créées
    - shell: nmcli connection del "Connexion filaire 2"
    - shell: nmcli connection del "ansible-eth1"//POur éviter de les stacker
      ignore_errors: True
    - shell: nmcli connection del "ansible-eth2"
      ignore_errors: True
    - shell: nmcli connection add ifname ethNBR con-name ansible-ethNBR type ethernet ip4 ADRESSE MACHINE/28 gw4 ADRESSE AUTREMACHINE (sert de passerelle)
(éventuellement) 
    - shell: nmcli connection add ifname ethNBR con-name ansible-ethNBR type ethernet ip6 ADRESSE MACHINE/28 gw6 ADRESSE AUTREMACHINE (sert de passerelle)
    - sysctl: name="net.ipv4.ip_forward" value=1 sysctl_set=yes state=present reload=yes (si passerelle ipv4)

ATTENTION : NBR = 0 ne doit pas être utilisé car elle est déjà utilisé par la VM

4/ Up la VM puis modifier le sshd en mettant le password à yes puis appliquer le fichier de config dans cd ../../vagrant

6/ Tester les pings entre machines ! Si le ping ne fonctionne pas essayer d'effacer les routes créées par défaut via : sudo ip route delete default
NOTE : La passerelle c'est un mec que vous connaissez que vous pouvez atteindre.
