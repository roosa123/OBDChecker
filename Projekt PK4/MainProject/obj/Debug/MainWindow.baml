   M S B A M L   `   `   `  ����F  BMainProject, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null)clr-namespace:MainProjectMainProject  5   	       MainProject.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   +localclr-namespace:MainProject     5   	   -   5          � Title$  Sprawdzacz OBD��5   	   $	��410��6    $	��940��6-    � WindowStartupLocation$ CenterScreen=�69   .��5	      � .+�5
   
   �� -   5         ��Name$ SearchButton��5
      $��Wyszukaj urządzenie��6'   $
��Left=�6E   $��	40,40,0,0q�6`   $	��Top=�6s   $	��150��6�   $��30��6�    �� 	IsDefault . {�. 6�   �� 5   
   -   5        $ RefreshButton��5      $��	Odśwież��6(   $
��Left=�6:   $��
40,110,0,0q�6U   $	��Top=�6i   $	��150��6�   $��30��6�    . {�.  6�   �� 5   
   -   5         ��Name$ ConstantReadCheckBox��5      $��Odczyt ciągły��61   $
��Left=�6I   $��
40,180,0,0q�6d   $	��Top=�6x   $��15��6�   {�.  6�   � 5   
   $
��Left=�6   $
��Auto��6*   $��
40,230,0,0q�68   $	��Top=�6L   $	��230��6d    � ColumnDefinitions 5      �� 5      $��90 �6#   �� 5      $	��140 �6#    � RowDefinitions 5      �� 5      $
��Auto �6    �� 5      $
��Auto �6    �� 5      $
��Auto �6    .+�5      �� -   5         ��Name$ ProtocolTextBlock��5      $
��Left=�63   $��0,5,0,0q�6N   $
��Wrap=�6_   $��Protokół:��6s   $	��Top=�6�   $��20��6�   �� 5      -   5        $ StandardTextBlock��5      $��1��63   $
��Left=�6@   $��0,5,0,0q�6[   $
��Wrap=�6l   $��Standard OBD:��6�   $	��Top=�6�   $��20��6�   �� 5      -   5        $ FuelTypeTextBlock��5      $��2��63   $
��Left=�6@   $��0,5,0,0q�6[   $
��Wrap=�6l   $��Typ paliwa:��6�   $	��Top=�6�   $��20��6�   �� 5      -   5        $  RetrievedProtocolTextBlock��5      $��1��6<   $
��Left=�6L   $��0,5,0,0q�6g   $
��Wrap=�6x   $��Nieznany��6�   $	��Top=�6�   �� 5      -	   5        $  RetrievedStandardTextBlock��5      $��1��6<   $��1��6L   $
��Left=�6Y   $��0,5,0,0q�6t   $
��Wrap=�6�   $��Nieznany��6�   $	��Top=�6�   �� 5      -
   5        $  RetrievedFuelTypeTextBlock��5      $��1��6<   $��2��6L   $
��Left=�6Y   $��0,5,0,0q�6t   $
��Wrap=�6�   $��Nieznany��6�   $	��Top=�6�   5      � 5   
   $
��Left=�6   $	��300��6*   $��
300,40,0,0q�67   $	��Top=�6K   $	��600��6c    5      �� 5       $	��200 �6#   �� 5!      $	��200 �6#   �� 5"      $	��200 �6#    5$      �� 5%      $	��100 �6    �� 5&      $	��100 �6    �� 5'      $	��100 �6    .+�5)      �� -   5         ��Name$ SpeedGroupBox��5)      $��Prędkość��6.   $
��Left=�6@   $��5,5,0,0q�6[   $	��Top=�6l   $	��190��6�   $��90��6�   .��5*      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5+      �� 5,      $	��80* �6+   �� 5-      $	��30* �6+   .+�5/      �� -   5        	 ��Name$	 
SpeedLabel��5/      $	��0.0��60   $
��Left=�6>   $��5,5,0,0q�6Y   $	��Top=�6j   $��20(�6�   $��37��6�   $��70��6�   �� 50      -   5        $ SpeedUnitTextBlock��50       $��1��6<   $
��Left=�6L   $��5,20,0,0q�6g   $
��Wrap=�6y   $
��km/h��6�   $	��Top=�6�   $��16��6�   $��28��6�   51      52      �� 53      -   5        $ EngineLoadGroupBox��53      $��Obciążenie silnika��63   $
��Left=�6O   $��5,5,0,0q�6j   $	��Top=�6{   $	��190��6�   $��90��6�   $��1��6�   .��54      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    55      �� 56      $	��80* �6+   �� 57      $	��30* �6+   .+�59      �� -   5        $	 EngineLoadLabel��59      $	��0.0��65   $
��Left=�6C   $��5,5,0,0q�6^   $	��Top=�6o   $��20(�6�   $��37��6�   $��70��6�   �� 5:      -   5        $ EngineLoadUnitTextBlock��5:       $��1��6A   $
��Left=�6Q   $��5,20,0,0q�6l   $
��Wrap=�6~   $��%��6�   $	��Top=�6�   $��16��6�   $��28��6�   5;      5<      �� 5=      -   5        $  CoolantTemperatureGroupBox��5=      $��Temperatura chłodziwa��6;   $
��Left=�6Z   $��5,5,0,0q�6u   $	��Top=�6�   $	��190��6�   $��90��6�   $��2��6�   .��5>      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5?      �� 5@      $	��80* �6+   �� 5A      $	��30* �6+   .+�5C      �� -   5        $	 CoolantTemperatureLabel��5C      $	��0.0��6=   $
��Left=�6K   $��5,5,0,0q�6f   $	��Top=�6w   $��20(�6�   $��37��6�   $��70��6�   �� 5D      -   5        $% CoolantTemperatureUnitTextBlock��5D       $��1��6I   $
��Left=�6Y   $��5,20,0,0q�6t   $
��Wrap=�6�   $	��°C��6�   $	��Top=�6�   $��16��6�   $��28��6�   5E      5F      �� 5G      -   5        $" EngineOilTemperatureGroupBox��5G      $#��Temperatura oleju silnikowego��6=   $
��Left=�6d   $��5,5,0,0q�6   $	��Top=�6�   $	��190��6�   $��90��6�   $��1��6�   .��5H      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5I      �� 5J      $	��80* �6+   �� 5K      $	��30* �6+   .+�5M      �� -   5        $	 EngineOilTemperatureLabel��5M      $	��0.0��6?   $
��Left=�6M   $��5,5,0,0q�6h   $	��Top=�6y   $��20(�6�   $��37��6�   $��70��6�   �� 5N      -   5        $&  EngineOilTeperatureUnitTextBlock��5N       $��1��6J   $
��Left=�6Z   $��5,20,0,0q�6u   $
��Wrap=�6�   $	��°C��6�   $	��Top=�6�   $��16��6�   $��28��6�   5O      5P      �� 5Q      -   5        $ FuelPressureGroupBox��5Q      $��Ciśnienie paliwa��65   $
��Left=�6O   $��5,5,0,0q�6j   $	��Top=�6{   $	��190��6�   $��90��6�   $��1��6�   $��1��6�   .��5R      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5S      �� 5T      $	��80* �6+   �� 5U      $	��30* �6+   .+�5W      �� -   5        $	 FuelPressureLabel��5W      $	��0.0��67   $
��Left=�6E   $��5,5,0,0q�6`   $	��Top=�6q   $��20(�6�   $��37��6�   $��70��6�   �� 5X      -   5        $ FuelPressureUnitTextBlock��5X       $��1��6C   $
��Left=�6S   $��5,20,0,0q�6n   $
��Wrap=�6�   $	��kPa��6�   $	��Top=�6�   $��16��6�   $��28��6�   5Y      5Z      �� 5[      -   5        $, &IntakeManifoldAbsolutePressureGroupBox��5[      $
��Left=�6G   $��5,5,0,0q�6b   $	��Top=�6s   $	��190��6�   $��90��6�   $��2��6�   $��1��6�   ��5\      �� 5]      $'��!Ciśnienie w kolektorze dolotowym��6    $	��120��6H   $
��Wrap=�6T   .��5_      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5`      �� 5a      $	��80* �6+   �� 5b      $	��30* �6+   .+�5d      �� -   5        $)	 #IntakeManifoldAbsolutePressureLabel��5d      $	��0.0��6I   $
��Left=�6W   $��5,5,0,0q�6r   $	��Top=�6�   $��20(�6�   $��37��6�   $��70��6�   �� 5e      -   5        $1 +IntakeManifoldAbsolutePressureUnitTextBlock��5e       $��1��6U   $
��Left=�6e   $��5,20,0,0q�6�   $
��Wrap=�6�   $	��kPa��6�   $	��Top=�6�   $��16��6�   $��28��6�   5f      5g      �� 5h      -   5        $" IntakeAirTemperatureGroupBox��5h      $
��Left=�6=   $��5,5,0,0q�6X   $	��Top=�6i   $	��190��6�   $��90��6�   $��2��6�   $��2��6�   ��5i      �� 5j      $%��Temperatura powietrza wlotowego��6    $	��130��6G   $
��Wrap=�6S   .��5l      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5m      �� 5n      $	��80* �6+   �� 5o      $	��30* �6+   .+�5q      �� -   5        $	 IntakeAirTemperatureLabel��5q      $	��0.0��6?   $
��Left=�6M   $��5,5,0,0q�6h   $	��Top=�6y   $��20(�6�   $��37��6�   $��70��6�   �� 5r      -   5        $' !IntakeAirTemperatureUnitTextBlock��5r       $��1��6K   $
��Left=�6[   $��5,20,0,0q�6v   $
��Wrap=�6�   $	��°C��6�   $	��Top=�6�   $��16��6�   $��28��6�   5s      5t      �� 5u      -    5        $ ThrottlePositionGroupBox��5u      $��Pozycja przepustnicy��69   $
��Left=�6W   $��5,5,0,0q�6r   $	��Top=�6�   $	��190��6�   $��90��6�   $��2��6�   .��5v      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5w      �� 5x      $	��80* �6+   �� 5y      $	��30* �6+   .+�5{      �� -!   5        $	 ThrottlePositionLabel��5{      $	��0.0��6;   $
��Left=�6I   $��5,5,0,0q�6d   $	��Top=�6u   $��20(�6�   $��37��6�   $��70��6�   �� 5|      -"   5        $# ThrottlePositionUnitTextBlock��5|       $��1��6G   $
��Left=�6W   $��5,20,0,0q�6r   $
��Wrap=�6�   $��%��6�   $	��Top=�6�   $��16��6�   $��28��6�   5}      5~      �� 5      -#   5        $. (RealtiveAcceleratorPedalPositionGroupBox��5      $$��Względna pozycja pedału gazu��6I   $
��Left=�6o   $��5,5,0,0q�6�   $	��Top=�6�   $	��190��6�   $��90��6�   $��1��6�   $��2��6�   .��5�      � $
��Left=�6   $��50��62   $��	10,10,0,0q�6>   $	��Top=�6Q   $	��160��6i    5�      �� 5�      $	��80* �6+   �� 5�      $	��30* �6+   .+�5�      �� -$   5        $+	 %RelativeAcceleratorPedalPositionLabel��5�      $	��0.0��6K   $
��Left=�6Y   $��5,5,0,0q�6t   $	��Top=�6�   $��20(�6�   $��37��6�   $��70��6�   �� 5�      -%   5        $3 -RealtiveAcceleratorPedalPositionUnitTextBlock��5�       $��1��6W   $
��Left=�6g   $��5,20,0,0q�6�   $
��Wrap=�6�   $��%��6�   $	��Top=�6�   $��16��6�   $��28��6�   5�      5�      5�      5�      5�      