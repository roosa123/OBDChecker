   M S B A M L   `   `   `  ����F  BMainProject, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null)clr-namespace:MainProjectMainProject  5          MainProject.SearchWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      +localclr-namespace:MainProject     5        � Title$  Wyszukiwanie urządzeń��5	      $	��500��6%   $	��350��61   .��5      � .+�5   
   �� -   5         ��Name$ InfoTextBlock��5      $
��Left=�6+   $��	75,50,0,0q�6F   $
��Wrap=�6Y   $	��Top=�6m   $	��350��6�   $��40��6�    �� Padding$ 4q�6�    �� TextAlignment$ Center=�6�   �� 6�   $I�CWyszukiwanie dostępnych urządzeń w toku. Może to potrwać ok. 1��6�   �� 6  $�5��6  �� 6  $� sekund. Proszę czekać��6   6A  �� 5   
   -   5         ��Name$ AvailableDevicesListBox��5      $
��Left=�63   $	��110��6N   $��
75,110,0,0q�6[   $	��Top=�6o   $	��350��6�   $��Center=�6�   
������ 6�   �� 5   
   -   5         ��Name$ ConnectButton��5      $��Połącz��6(   $
��Left=�69   $��
75,260,0,0q�6T   $	��Top=�6h   $	��150��6�   $��30��6�    �� 	IsDefault . {�.  6�   �� 5   
   -   5        $ CancelButton��5      $��Anuluj��6'   $
��Left=�68   $��275,260,0,0q�6S   $	��Top=�6h   $	��150��6�   $��30��6�    �� IsCancel . 6�   5      5      