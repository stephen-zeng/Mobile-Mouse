<h1 align="center">
  <br>
  <img src="https://raw.githubusercontent.com/stephen-zeng/Mobile-Mouse/master/android_icon.png" width="150"/>
  <br>
  Mobile Mouse
  <br>
</h1>
<h4 align="center">将手机当电脑鼠标操作</h4>

# 特色 #
+ 两种操作方式：按钮操作和**陀螺仪操作**
+ 基于原生Qt开发，性能优秀
+ 多平台支持，支持Windows，macOS，Android
+ 多架构支持，支持arm64和x64双架构

# 效果 #
![](https://raw.githubusercontent.com/stephen-zeng/Mobile-Mouse/master/demo.gif)

# 使用 #
直接从[release页面]()下载对应版本，iOS版本需要自己签名（OACD）。使用方法在APP中均有体现。
+ 对于安卓设备，本机设备的名称在各系统的**关于本机**处查看。
+ Windows客户端扫描设备时会出现一堆`Bluetooth **:**:**:**`，不用管，找到自己的设备连接就好。
+ 移动端的连接状态可能会更新不及时，以电脑端的连接状态显示为准

# 二次开发 #
项目使用的Qt版本为**6.8.0 LTS**，在安装Qt时，需要安装一下组件（Additional Libraries）：
+ Qt Sensors
+ Qt Connectivity

Windows则需要安装MSVC_2022编译器，不能使用MinGW编译，因为这样蓝牙无法使用。
安卓