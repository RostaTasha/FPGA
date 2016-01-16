1.  Hardware Design Exercise

This is the  exercise for hardware designers. It consists of two parts. The first part is to design and verify a digital module. The later part is to prototype the design with Altera Quartus II, optimize for performance and meet timing requirements. The target is a Cyclone V FPGA.

A set of embryo files for the Verilog design, the C++ verification code and the Quartus project are provided in the archive accompanying this exercise. The file _quartus\_howto.txt_ which is also included contains instructions on how to install and configure Quartus, while _simulation\_howto.txt_ describes how to build and run a simulation and examine the waveform.

1.
  1. Module Description

The task is to implement a calculator capable for three mathematical operations: addition, subtraction and multiplication. Each arithmetic operation is conducted in a different arithmetic unit. An independent input interface is used for each arithmetic unit. The interface consists of a _valid/ack_ handshake pair and two arithmetic operands.  The arithmetic units should accept an input whenever the _valid_ signal is high and they are not blocked due to congestion further down in the pipeline.  An arbiter is responsible to fairly arbitrate between the output of the arithmetic units and propagate them to a common output interface. In addition to the _valid/ack_ and _data_ outputs, an additional output _result\_unit_ is showing which arithmetic unit the result came from.
 ![](data:image/*;base64,iVBORw0KGgoAAAANSUhEUgAAATEAAAGeCAYAAAD8LzZTAAAqVklEQVR4nO3dCXQUVdoG4A8IW8ISFpHIIou4IKggGDZZArIjEFYZ3BA8Ao6CgwsuIKOOygCKioiAogI6g+KGDEcdFEERRGXUQVRUlH0HWRLD9vN+/9/5Q+xOupOurvqq3+ecHJJO01yqut6uunW/exNOniIu2r9/vzRr1kzWr18fk39v0qRJkpCQIKNGjYrJv0fkhu3bt0vnzp1l7dq1rvz7sTzOEhz/F6IIeYuvokWLut2UuJLXGzKWb1Z+AMWGteOs0CGGxO/QoYM0btxYPvnkE7n00ktlxIgRcuedd8rOnTtl9uzZ0q5dOz3Tuummm+TDDz/Uv/fII49IqVKl5Lrrrsv39du0aSMtW7aUbdu2yfPPPy8rVqyQiRMnyrFjx+TCCy+UWbNmScmSJaVjx46ye/duycrKkjFjxmS/9mOPPSYzZsyQSpUqSZ06dbSNMG7cOKlYsWL2QXHPPfdIlSpV5NZbby3sZqFcrB0YXoSrlv79+8uePXv0vT9hwgQ5//zzgx5XAwcOlKNHj8pVV10l//3vf/V9P3fuXClTpkzQ13bqOIvFMRaVMzEE1Lx58+SFF16Q9u3by/Tp0zXQPvvsMw0zhFhh/Pjjj/LWW2/JeeedJxs3bpSnnnpKli9frht0/PjxMnPmTLn55pvllVde0Q2WkZGhOyM9PV22bt2qG3bNmjVSpEgRadKkSXaIDRkyRJ+DDXzixAn9+6tXr47GJjEj0uDP73c5WT4wvOjNN9+Uhg0byuTJk/XngwcPypYtW0I+f926dXoSge6a22+/XaZMmaLbLhQnjrNYHGNRCbF69erJxRdfrN9fcskl+ubEJ26jRo10YxRW3bp1dcMCPnHwmp06ddKfsSHT0tL0+2nTpsmSJUv0kmPTpk3y008/6Ubt3r179icQNmhArVq19OD48ssvZceOHdpe/BxPIg1+fGCF+l0wVg8ML8LVDs6+SpQoIT169JAWLVrk+fzatWtrgMHgwYP1wyEvThxnsTjGohJieEMGILwCP+N7fOLqP3TqP4w3XAA+cXHaG47SpUtnf49LEnRYPvPMM6c9591339Wzvw8++EB3Mp6TmZmpvytevHj283J+D0OHDpU5c+boWQMOjngTafDjTCrU74KxemB4Ec7CENaLFy+WsWPHSrdu3XSbFPS4ys2p48zpYyxmHfspKSmyefNmOX78uH6qYiP07Nkz4tdp27atXj7ccccdenmBfgL0Eezbt08/ebBh8cbGhoZWrVrpp33g38VOQL9CQO/evfUUG/0H8+fPj9r/14KCBn9ev8vN6oHhRTh+zjjjDLnmmmv0rBVdOCNHjgx5XP3888+ycuVKad68ubz00kvSunXrsP+taB5nTh9jMQuxpKQkGT58uG6catWqFfiTExsQfW7YMNgoeGNPnTpVT6/RJ4cNh09unHoDOj7RyYlP/zPPPFNq1qx52uthZ6DPLjk5WYoVK1bo/6clBXlD5vehkBdLB4YX4cz0vvvu0/cpzrZwqZ3XcVW/fn154okn5IYbbtAuH4ReuKJ5nDl9jBU6xKpWrXraWBTcBs9+8VOXBviUCEDnIr5yy2uMWO7XB3zSBDuLw2l2MKNHj9avYHAq/umnn8qCBQtCtsGvCvKGzO9DIS+WDgwv6tWrl37lFuq4wl3JcDl5nDl9jJkaJxZtuHuDPhccVPikijeJiYkFCv68fpeT5QODoiMWx5hnQmzv3r1BO4kXLlyo1/9OwOk2OpDJlnj/8CmMWB9nsTjGPBNi2ICBAXtkix8PDL/y43HmmRAju/x4YPiJk3WUOWuf86qDdrJkzDMhFu1CcC9sXD8Ktb2iuR2572wqW7asK3eKPRNiTnJr41Lhcd/9USQ1lIGAD7eO8q677pIaNWro+DO4//779XkY7R+qNCwAZVCDBg3K/sAJtzytsKIWYk4XglvcuJbktQ1Dba9wtyP3XXRFWkMJ4dZRDhgwQIMvsK9w9xeVFBCsNCyUSMvTCiOqZ2JOFoJb3LiWBNuG5cqVC7m9ItmO3HfRFWkNJYRbR4kSLpx0oG51165dUqFCBf0AgmClYSgBCybS8rTCiGqIOVkIbnHjWhJsG2IfhtpekWxH7rvocrqGsl+/fvLqq6/q1RUGG0NepWGhRFKeVhhRDTGnC8GtbVwr8tuGobZXJNuR+y56Iq2hhEjqKHHmPGzYML3Mx4wjEKo0LJTClKdFKuYd+4UpBLe2ca3IaxuG2l6Rbkfuu+iJtIYSIqmjxBUU+tlQ5oVyLwhVGhZKYcrTIhXzECtMIbi1jWtFXtsw1PaKdDty30VPpDWUKP+KpI4Svv7669N+zqtELXDTBXWsOYfChFueVlhRCzGnC8EDLG1cK/LahhBqe0W6HbnvyAlxMU6MiE7nRq2yUzwXYn7auPGG+84OP5WKeS7E/LRx4w33HbnBcyGWl1gvtEsUL9xebLcwTIUYeZ9XFtql+BHTEHO6vhLyq8UjigdOFomDl46zmJ+JOb3QbqgaQCo8Jxfazev1KXJOFomDl46zmIeY0wvthqoBpMJzeqFdLx0Y1jlZJA5eOs5iHmJO1lcWpBaPwuf0QrteOjCsc7JI3GvHmSc79gtaXxlpLR6Fz+mFdr12YFjnZJG4144zT4ZYQesrI63Fo/A5vdCu1w4M65wsEvfacRbTEHO6vjK/GkAqOKcX2vXagWGdk0XiXjvOPHkmRt7j9EK7XjswyA6TIcYaPSLnWTnOTIYYa/TssnJgkJ3jzGSIkV1WDox4EmndpNfqLE2FWH4F4F7buPGooLWT3HdUUKZCjIjCE0ntJO4gR1I3CZE+30m+KwD30sb1G6drJ7nvoifS2slI6iYL8nwn+a4A3Esb12+crp3kvoueSGsnI6mbLMjzneS7AnAvbVy/cbp2kvsuepxeYNdLfFUATs5xunaSoivS2slIFtctyPOd5MmO/cIssOuljesnTtdOAvdd9ERaOxnJ4roFeb6TPBlihVlg10sb10+crp0E7rvoibR2MpLFdQuyGK+TfFUA7rWN6ydO105y31FBefJMjIjcZ6VEzGSIWdm49Efcd3ZYKREzE2JHjhzRUchly5Y1s3Hj3eHDh+XAgQNSvnx57ecE7jtvw6BYfCUnJ2sXggVmQgx3uHBLn0Mt7MCQGeyzQICR96FqAvsMx5sVZkKMiCgYhhgRmcYQIyLTGGJEZBpDjIhMY4gRkWkMMSIyjSFGRKYxxIjINIYYEZnGECMi0xhiRGQaQ4yITGOIEZFpDDEiMo0hRkSmMcSIyDSGGBGZxhAjItMYYkRkGkOMiExjiBGRaQwxIjKNIUZEpjHEiMg0hhgRmcYQIyLTPBtihw4dkoMHD0pKSkqhnkOxs2fPHilSpIhUrFgx5HP27t0rJ0+elEqVKsWwZRTKtm3bpGzZslKmTJk8n1OuXDlJSkqKYcvC59kQw0bt37+/zJo1S84666w//B4Blp6eLm+88YYLraNgkpOTpXPnzvKPf/wjaJAh5AYOHChLlixxoXUUTPny5aVXr16ycOHCoEG2detWGTp0qCxevNiF1oXHsyEGCK8mTZrImjVr9NMiAGdfLVu21E+HxMREF1tIORUrVkz3R9OmTWX16tWSkPD/by8EGB6/6KKL9HnkDdhfhw8flhYtWsjHH3982u+2bNmi+6xbt24utS48ng4xfELMmTNHN+TSpUulePHiegaGjbpu3TqZPHmy202kXPr06SOLFi3Sffbvf/9bH0OAdejQQX755ReZMGGCyy2k3Pr27StjxozRIHvnnXf0MQRYWlqa7Ny5U49DL/N0iLVv315KlCgh27dvl8svv1yeffZZ+ctf/iKbNm3S6/OePXu63UTKpWvXrlKqVCndR9hnTz/9tIwYMUJ27Nihj3fp0sXtJlIuPXr0kPHjx8t3332nwTVp0iS58cYb9cOnZMmSehx6madDrHTp0tKwYUO9NEGHMD7lcYly9OhRqVChgtSuXdvtJlIulStXlmrVqskPP/ygwYVPceyzY8eOSZ06dfT35C3nnHOOHmvoptm8ebMeZ7hBc+LECb38x4ePl3k6xAAdwd98840cOXJEf87KypKiRYvKlVde6XLLKBRcnuDTHB82gD/RFYDHyZtwNvbcc8/J77//nv0Y+stw/Hmd50Ose/fueqqbEzr08WlB3oTL/OnTp8v+/fuzH+Plv7fheHrttddO22e4AYPjz+s8H2L16tXTTwSc6gbg06Jt27buNYryhE59XIrkhJ9xp5m8CcdTzrMwwHGHS02v83yIAU51Z8+erYMkoVGjRp6/To9nuNzHQfHWW29lP9auXTt9nLwJfWKXXHKJrFy5Un9Gn5iVLhsTIYZBrQsWLJADBw7oxrZwnR7vMFAZw2IwJCYwcJm8DcfV2rVrJSMjQ7tscNxZYCLE8KmODn2wcp0e7zp16iTHjx/X7/Fnx44dXW4R5QfDY+699179HseblS4bEyGGs68GDRrIZ599ptfpHFrhfYGhFhs2bJDq1atzaIUB6P9CNw36nzG0yUqXTUJmZqbbbQhL79695fPPP9faPCttxkBB9C1EE/oFc3fAehX6VB5//HH9k/vMxj7D8TVv3jy9lLSyzxJQoW5Bs2bN9A4XOoittBlnIBgfFU04IKz8/1u1aiVTpkzRP620+eyzz456iGGgr5X/P46vl156SVJTU8202cTlJNSqVUtPdy+77DK3m0JhwiUJQgFdAWQDwgvHGfabFWZCDO6++27tHyMbcBMGA5U5a4UdOL5wnFliKsSs3C2h/8d9Zo+1fWYqxIiIcmOIEZFpDDEiMo0hRkSmMcSIyDSGGBGZxhAjItMYYkRkGkOMiExjiBGRaQwxIjKNIUZEpjHEiMg0hhgRmcYQIyLTGGJEZBpDjIhMY4gRkWkMMSIyjSFGRKYxxIjINIYYEZnGECMi0xhiRGQaQ4yITGOIEZFpDDEiMo0hRkSmMcSIyDSGGBGZxhAjItMYYkRkmqkQS09Pl4ULF7rdDCLyEM+H2NKlS+XgwYPSs2fP7MfeeOMNKVeunKSlpbnYMgrHyJEjpXnz5jJ48GC3m0I+5fkQa9asmcycOVOGDRsme/bs0T8bNGigf5L3ZWZmSlZWltvNIB/zfIglJibKkCFD5IEHHpCtW7dKamqq/ozHiYg8H2IrVqyQqVOnyujRo2XDhg16WYkQGzVqlLRs2dLt5hGRyzwfYrh0nD9/vhQvXlx/RnA1bdpUjhw54nLLKJjHH39cpk2blv3ziRMnZNmyZfLwww9nPzZ37lw9oyb3vf/++zJ8+PDsnx999FG9gWaJ50MsOTk5+/u+ffvqnyVKlNAv8p6rr75aunbtmv3zuHHjpHHjxtKrV6/sx6pXr+5G0yiIFi1ayJIlS7J/rlKlioutKRjPh1hOgwYNcrsJlI9KlSrpV0BSUpJUrlxZzj33XBdbRaGgb7lu3bpuN6NQTIUYEVFuDDEiMo0hRo6aPXu2200gn2OIEZFpDDEiMo0hRkSmMcSIyDSGGBGZxhAjItMYYkRkGkOMiExjiBGRaQwxIjKNIUZEpjHEiMg0hhgRmcYQIyLTGGJEZBpDjIhMY4gRkWkMMSIyjSFGRKYxxIjINIYYEZnGECMi0xhiRGQaQ4yITGOIEZFpDDEiMo0hRkSmMcSIyDSGGBGZxhAjItMYYkRkGkOMiExjiBGRaQwxIjKNIUZEpjHEiMg0hhgRmcYQIyLTGGJEZFpCsWLF3G6DbxUpUsSR1+U+swXvA+4z5yTUrFnT7TaEJSMjQ3777TdJSkqSMmXKuN0c1xQtWlSs7LMjR47IwYMHpWzZspKYmOh2c1yTkJBgZp8dOnRIDh8+LOXKlZPSpUu73ZywmLmcPHbsmG7c4sWLu90UCtPRo0d1n5UqVcrtplCYsrKydJ9Z+tAxE2JERMEwxIjINIYYEZnGECMi0xhiRGQaQ4yITGOIEZFpDDEiMo0hRkSmMcSIyDSGGBGZxhAjItMYYkRkGkOMiExjiBGRaQwxIjKNIUZEpjHEiMg0hhgRmcYQIyLTGGJEZBpDjIhMY4gRkWkMMSIyjSFGRKYxxIjINIYYEZnm2RA7fPiw/P7771KxYsWQz8HvDxw4IFWqVIlhyyiUvXv3SokSJaRMmTIhn3Po0CE5evSoVKhQIYYto1B27twp5cuXl5IlS4Z8DvYrfp+UlBTDloXPsyGGDTZo0CB57rnnpFKlSn/4fWZmpgwcOFBeeuklF1pHwZQtW1bS09Pl5ZdfDhpkBw8e1H36+uuvu9A6CqZ06dJ6HL3yyitBg2zPnj0yZMgQefPNN11oXXg8G2KQnJwsqampsmrVKv2ED0CAdejQQY4fP64HDnlD8eLF5cSJE9KqVStZvnz5ab9DgOHxGjVqSEKCp992cQXHz7Zt2/R4eu+990773e7du6VZs2a637zM0++mXr16ydy5c6Vp06aydOlSfQyXkN26ddNge+SRR1xuIeWGM7Ebb7xRWrRoIUuWLNHHEGCdO3eWb7/9Vm699VaXW0i59e7dW8aOHStpaWny2muv6WM4A2vXrp38+uuvMmnSJJdbmDdPh1jHjh2lVKlSuiFbtmwpL774oowaNUp++OEHKVeunFx55ZVuN5FywQdMYmKifPfdd9K6dWuZOXOmDBs2TDZt2qSPd+3a1e0mUi44jnBC8MUXX+gx9/jjj8s111wjO3bs0OPviiuucLuJefJ0iKFf7LzzzpMvv/xSdu3aJZ06ddJLFpyNoc/l/PPPd7uJlEvVqlWlcuXKsnHjRtm8ebPus6JFi2pnfvXq1fX35C0XXHCB7iMcVxs2bMjeZ+iuwTHm1Q79AE+HGAwYMEDWr18vGRkZ+jM2bJEiRfiJ7mF9+vSRqVOnSlZWVvZj6AfD4+RNOJ7mzZun/c2A4wyd/jj+vM7zIdajRw95+OGHs0MMcEu4X79+LraK8oK+TNxV3rdvX/Zj6EDG4+RNOJ4WLVok+/fvz34MN9Nw/Hmd50Osfv36egmZEz7h0QlJ3tS8eXM5duzYaY/hZ9zpIm9q3779aWfOgOMOl5pe5/kQA5zqYjzYyZMn9ecLL7zQ89fp8axYsWJ6IyZwdxJwmx6PkzfheMIJw5o1a/RndNngJo0FJkIMfSkYbIfR+bhbYuE6Pd5hH2GsGCovcBOG+8z7sI+++eYb7RfD3X8rfZgmQiznqS6u0618QsQzjAsLnDljACzueJG34bh64IEHNMRwN9lKl42JEAsMtVi7dq2GGIdWeB+GUqCmFUMtzjzzTA6tMAD9X4FqChxvVrpsTIQY4O7JV199pYPxyAbcjXziiSekZ8+ebjeFwoQzaNRRWrr7bybEcEDcc889WqxKNqBPBaO/+/bt63ZTKEzoF5s/f76p4TBmQgx3TurUqSNt27Z1uykUJhTv16xZU/8kG1AviePMwtCKADMhBhMnTuSsFYZgnNGUKVM4a4UhOL5wnFli6t2FGRLIFu4ze6ztM1MhhgF4ZAv3mT3W9pmpECMiyo0hRkSmMcSIyDSGGBGZxhAjItPMhRimqsZUPDlXPyKi6Ni+fbtOU3322We73ZSwmQuxxx57TFc6mjx5snTv3t3t5lAesBQYDopGjRq53RTKB4ILU4r//e9/19WNrr32WrebFDZzIYYVj5YtW6arHmFjozbvkksucbtZFMTq1atl8eLFMmPGDLebQiFguiRMOIq6ZJQcYaaYatWqud2siJgLMWjTpo18/vnnuiZlly5ddEkpfIJgyhciCs+nn36q64BiZSOsN3nZZZe53aQCMRligA2PtfECa+ZdfPHFMnr0aD1DC7YcOxH9L1zi33HHHfL+++/rsXP11VebG6Wfk9kQC0hOTtYdccMNN8htt90ms2fP1qJj9pcRnQ79Xlg57KmnnpKbb75ZF6G2MvFhXsyHWEC9evXk7bff1k8XnI2hkxL9ZbiTSRTvFixYoP1e6D/GZeQ555zjdpOixjchFtChQwcdhvH000/r3GODBg2SCRMm6BkbUbzBwh/4UN+xY4dMnz5d16vwG9+FGGAeK3RY4lofAYb5wu+++249heayYRQPdu/erWdeuDq5//77ZciQIb6d182f/6v/U7FiRb2svP766zXU5syZoz+3bt3a7aYROQKLFE+bNk0eeughueqqq/RMDMeBn/k6xALQD4CxZfhUuu6667SfDAtY1K5d2+2mEUUNFivGHfpatWrJRx99FDergsVFiAX06NFD+8wQYM2aNdMzNJxyc8prsuynn37SK41169bpzSy8z+NJXIUYlC5dWu68807tL7vrrrt0QYS//e1v5sfKUPz57bff5L777pN58+bpnxiwGo81xXEXYgFnnXWWljB99tln+imGsTPoL2ve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)

 ![](data:image/*;base64,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)

**Valid/ack interface**

This interface connects a sender (producing a datum) and a receiver (consuming a datum) in such a way that the sender and the receiver both have the ability to regulate the speed. The _valid_ signal go from the sender to the receiver, while the _ack_ signal goes from the receiver to the sender. Any number of additional signals can be present in order to transfer data from the sender to the receiver. _Valid_ high signifies that there is _valid_ data on these ports, while _ack_ signifies that the receiver has accepted the data. Thus, such transfer occurs if and only if both _ack_ and _valid_ are asserted at a rising clock edge. The _ack_ signal is combinatorial and based in part on the _valid_ signal  _ack_ should never be high unless _valid_ is also high.



1.
  1.
    1. Requirements

1. 1.Arithmetic units should accept calculation commands as often as possible
2. 2.Arithmetic units use have a _valid/ack_ input interface. An operand set is accepted with the assertion of the _valid_(sender) and _ack_(receiver) signals within the same cycle. Any other state of the _valid_ and _ack_ signals should not trigger calculations or cause output changes.
3. 3.All results should be propagated to the test-bench through a streaming interface. The test-bench should have the ability to stall the output by holding _ack_ de-asserted. An output is accepted only when the _valid_ and _ack_ signals are asserted within the same cycle. In any other case the calculator should maintain the _valid_ signal asserted and the _result_ value set, until the test-bench acknowledges the acceptance of an output
4. 4.The output of the module is **fairly** selected among the valid outputs of the three arithmetic units.
5. 5.Under-utilizing any of the arithmetic units should not cause idle cycles for the output interface. The only case when the output _valid_ signal can be de-asserted is when no arithmetic unit has completed a calculation
6. 6.All calculations should be mathematically correct
7. 7.The one-hot encoded output signal _result\_unit_ is showing which arithmetic unit is selected for output when the _valid_ signal is asserted

1.
  1. Design Verification

A randomized test written in C or C++ should be provided with the above design. It should fully randomize the inputs in order to ensure that the module is driven into all the relevant states, while checking that module behaves correctly. The test code must be easily understandable, and robust (not error-prone). You may create more than one test with different types of randomized stimuli if you feel that this is required, but in our experience, one or two tests, and 100-200 lines of code (semicolons) is all it takes. Consider the requirements related to correct mathematical results, fairness and throughput, and make sure your checking logic will catch all bugs. As part of the code review, we might try to insert bugs into the Verilog code to see that the test detects them.

1.
  1. Design Prototyping

When the design is complete and verified, it has to be synthesized and fitted for an Altera Cyclone V FPGA. You should only be using the synthesizable subset of the Verilog or SystemVerilog language for that reason. Once this is complete, observe the maximum operation frequency in the TimeQuest Timing Analyzer (Fmax summary).

1.
  1. Design Optimization

The goal for this last part of the exercise is to beat the maximum frequency Quartus achieves when synthesizing Verilog behavioral code ( a <= c + b) .

Quartus recognizes operands such as \* and +, and synthesizes them into combinatorial logic in the most efficient way for your FPGA. However, for wide operands, the critical path may become too long. The best way to overcome this, is to combine the result of multiple narrower calculations in a pipeline.

Identify the critical path in the design. Optimize the design to reach a maximum operating frequency of 150Mhz.

To understand what pipeline is, and how to improve timing in designs you might consult the following lecture handouts:

 Lecture 1. Implementing Algorithms I [(2/page pdf)](http://www.imit.kth.se/courses/IL2204/F1_2.pdf) [(6/page pdf)](http://www.imit.kth.se/courses/IL2204/F1_6.pdf)

 Lecture 2. Implementing Algorithms II [(2/page pdf)](http://www.imit.kth.se/courses/IL2204/F2_2.pdf) [(6/page pdf)](http://www.imit.kth.se/courses/IL2204/F2_6.pdf)

 Lecture 3. Implementing Algorithms III [(2/page pdf)](http://www.imit.kth.se/courses/IL2204/F3_2.pdf) [(6/page pdf)](http://www.imit.kth.se/courses/IL2204/F3_6.pdf)

Please note that these lecture handouts are not FPGA specific and do not take into account that FPGA devices might have dedicated hardware for efficient multiplication.





_GOOD LUCK!_