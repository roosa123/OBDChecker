   M S B A M L   `   `   `  ����F  BMainProject, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null)clr-namespace:MainProjectMainProject  5          MainProject.PinInput   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      +localclr-namespace:MainProject     5        � Title$  PIN urządzenia��5	      $	��300��6   $	��500��6+   .��5      �  +� FocusedElement 6   ��  �� ElementName$ 
PINTextBox��.+�5   
   �� -   5         ��Name$ QuestionTextBlock��5      $
��Left=�6/   $��
100,50,0,0q�6J   $
��Wrap=�6^   $5��/Proszę podać numer PIN wybranego urządzenia:��6r   $	��Top=�6�   $	��300��6�   $��35��6�    �� TextAlignment$ Center=�6�   5      � 5   
   $
��Left=�6   $��30��6*   $��175,115,0,0q�66   $	��Top=�6K   $	��150��6c   .+�5      �� -   5         ��Name$ 
PINTextBox��5      $
��Left=�6*   $��30��6E    �� TextWrapping$
 Wrap=�6Q   $	��Top=�6e   $	��150��6}   $��7q�6�    �� TextAlignment$ Center=�6�   6�   �� 5      $��	Numer PIN��6   $	��Top=�6)   $��Center=�6A   
������� J� IsHitTestVisible .  	 �� Padding$	 7q�6�   ��5      �� 5      
 �� 
TargetType"
 ��6   .�5      ��  �� Property � y� �� Value$ 	Collapsed=�67    �� Triggers 5      �� 5       �� Binding 6*   �� *Text+$ 
PINTextBox�� �� Value  6[   .a�5   "   ��  � y�$ Visible=�6?   5      5      5      5      �� 5   
   -   5         ��Name$ ConfirmButton��5      $��OK��6(   $
��Left=�65   $��100,190,0,0q�6P   $	��Top=�6e   $	��100��6}   $��25��6�    �� 	IsDefault . {�.  6�   �� 5   
   -   5        $ CancelButton��5      $��Anuluj��6'   $
��Left=�68   $��300,190,0,0q�6S   $	��Top=�6h   $	��100��6�   $��25��6�    �� IsCancel . 6�   5      5       