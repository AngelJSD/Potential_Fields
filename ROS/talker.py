#!/usr/bin/env python
# license removed for brevity
#import roslib; roslib.load_manifest('nxt_ros')
#import rospy
import time

from PIL import Image
#from std_msgs.msg import String
#from nxt_msgs.msg import JointCommand
#from nxt_msgs.msg import Range

#pub = rospy.Publisher('joint_command',JointCommand)
im = Image.open('mapa1.png')
#def callback(effort):
    #rospy.loginfo(rospy.get_caller_id()+"I heard %s",str(data.range))
    #if(data.range>1.0): 
#    if effort=='f':
#	start = time.clock()
#        end = time.clock()
#	while(end - start<0.1):#0.1s=10cm :D
#            pub.publish('motor',10)
#            pub.publish('motor1',10)
#            end = time.clock()
#        print end
#	pub.publish('motor',00)
#        pub.publish('motor1',00)
#    if effort=='b':
#	start = time.clock()
#        end = time.clock()
#	while(end - start<0.1):#0.1s=10cm :D
#            pub.publish('motor',-10)
#            pub.publish('motor1',-10)
#            end = time.clock()
#        print end
#	pub.publish('motor',00)
#        pub.publish('motor1',00)
#    if effort=='l':
#        start = time.clock()
#        end = time.clock()
#	while(end - start<0.2):#0.1s=10cm :D
#            pub.publish('motor',10)
#            pub.publish('motor1',00)
#            end = time.clock()
#        print end
#	pub.publish('motor',00)
#        pub.publish('motor1',00)
#    if effort=='r':
#        start = time.clock()
#        end = time.clock()
#	while(end - start<0.2):#0.1s=10cm :D
#            pub.publish('motor',00)
#            pub.publish('motor1',10)
#            end = time.clock()
#        print end
#	pub.publish('motor',00)
#        pub.publish('motor1',00)
#    if effort=='s':
#        pub.publish('motor',00)
#	pub.publish('motor1',00)

## luminance conversion formula from
## http://en.wikipedia.org/wiki/Luminance_(relative)
def luminosity(rgb, rcoeff=0.2126, gcoeff=0.7152, bcoeff=0.0722):
    return rcoeff*rgb[0]+gcoeff*rgb[1]+bcoeff*rgb[2]

## take a PIL rgb image and produce a factory that yields
## ((x, y), (r, g, b)), where (x, y) are the coordinates
## of a pixel, (x, y), and its RGB values.
def gen_pix_factory(im):
    num_cols, num_rows = im.size
    r, c = 0, 0
    while r != num_rows:
        c = c % num_cols
        yield ((c, r), im.getpixel((c, r)))
        if c == num_cols - 1: r += 1
        c += 1

## take a PIL RBG image and a luminosity conversion formula,
## and return a new gray level PIL image in which
## each pixel is obtained by applying the luminosity formula
## to the corresponding pixel in the RGB image.
def rgb_to_gray_level(rgb_img, conversion=luminosity):
    gl_img = Image.new('L', rgb_img.size)
    gen_pix = gen_pix_factory(im)
    lum_pix = ((gp[0], conversion(gp[1])) for gp in gen_pix)
    for lp in lum_pix:
        gl_img.putpixel(lp[0], int(lp[1]))
    return gl_img

## take a gray level image an a gray level threshold
## and replace a pixel's gray level with 0 (black) if
## its gray level value is <= than the threshold and
## with 255 (white) if it is > than the threshold.
def binarize(gl_img, thresh=70):
    a=[]
    im = Image.open('mapa1.png')
    gen_pix = gen_pix_factory(gl_img)
    cont = 0
    s=[]
    for pix in gen_pix:
        if pix[1] <= thresh:
            gl_img.putpixel(pix[0], 0)
            if(cont < im.size[0]):
                s.append('O')
                cont = cont + 1
            else:
                a.append(s)
                s = []
                cont = 0
                s.append('O')
                cont = cont + 1
        else:
            gl_img.putpixel(pix[0], 255)
            if(cont < im.size[0]):
                s.append(0)
                cont = cont + 1
            else:
                a.append(s)
                s = []
                cont = 0
                s.append(0)
                cont = cont + 1
    return a  

def absoluto(x):
	if(x<0):
		return x*(-1)
	return x

def camino(a,r,nobs,o,g,matrix):
	k=0
	ruta=[]
	menor=0
	temp=''
	for i in range(50):
		for j in range(50):
			atraccion=(1/2.0)*absoluto(j-g[1])*absoluto(j-g[1])+(1/2.0)*absoluto(i-g[0])*absoluto(i-g[0])
			k=0
			while(k<nobs):
				#print k
				if(absoluto(j-o[k+1])==0 and absoluto(i-o[k])==0):
					a[i][j]=atraccion
				elif(absoluto(j-o[k+1])==0):
					a[i][j]=1/(absoluto(i-o[k])*1.0)+atraccion
				elif(absoluto(i-o[k])==0):
					a[i][j]=1/(absoluto(j-o[k+1])*1.0)+atraccion
				else:
					a[i][j]=1/(absoluto(j-o[k+1])*1.0)+1/(absoluto(i-o[k])*1.0)+atraccion
				k=k+2
	#a[g[0]][g[1]]='G'
	direccion=0
	while(True):
		print (matrix[r[0]+1][r[1]])
		menor=1000000
		if(r[0]+1<50):
			print ('m')
			if(matrix[r[0]+1][r[1]]=='G'):
				break
			if(matrix[r[0]+1][r[1]]!='O' and matrix[r[0]+1][r[1]]!='R' and a[r[0]+1][r[1]]<menor and direccion!=3):
				print ('a')
				menor=a[r[0]+1][r[1]]
		if(r[0]-1>-1):
			if(matrix[r[0]-1][r[1]]=='G'):
				break
			if(matrix[r[0]-1][r[1]]!='O' and matrix[r[0]-1][r[1]]!='R' and a[r[0]-1][r[1]]<menor and direccion!=1):
				print ('b')
				menor=a[r[0]-1][r[1]]
		if(r[1]+1<50):
			if(matrix[r[0]][r[1]+1]=='G'):
				break
			if(matrix[r[0]][r[1]+1]!='O' and matrix[r[0]][r[1]+1]!='R' and a[r[0]][r[1]+1]<menor and direccion!=4):
				print ('c')
				menor=a[r[0]][r[1]+1]
		if(r[1]-1>-1):
			if(matrix[r[0]][r[1]-1]=='G'):
				break
			if(matrix[r[0]][r[1]-1]!='O' and matrix[r[0]][r[1]-1]!='R' and a[r[0]][r[1]-1]<menor and direccion!=2):
				print ('d')
				menor=a[r[0]][r[1]-1]
		if(r[0]+1<50 and a[r[0]+1][r[1]]==menor):
			#if(matrix[r[0]+1][r[1]]=='H'):
			#	matrix[r[0]][r[1]]='R'
			#	matrix[r[0]+1][r[1]]='R'
			#else:
			matrix[r[0]+1][r[1]]='H'
			if(direccion==2):
				ruta.append('r')
			#if(direccion==4):
			#	ruta.append('l')
			direccion=1			
			ruta.append('f')
			r[0]=r[0]+1
		elif(r[0]-1>-1 and a[r[0]-1][r[1]]==menor):
			#if(matrix[r[0]-1][r[1]]=='H'):
			#	matrix[r[0]][r[1]]='R'
			#	matrix[r[0]-1][r[1]]='R'
			#else:
			matrix[r[0]-1][r[1]]='H'
			#if(direccion==2):
			#	ruta.append('l')
			#if(direccion==4):
			#	ruta.append('r')
			direccion=3			
			ruta.append('b')
			r[0]=r[0]-1
		elif(r[1]+1<50 and a[r[0]][r[1]+1]==menor):
			#if(matrix[r[0]][r[1]+1]=='H'):
			#	matrix[r[0]][r[1]]='R'
			#	matrix[r[0]][r[1]+1]='R'
			#else:
			matrix[r[0]][r[1]+1]='H'
			if(direccion==1):
				ruta.append('l')
			if(direccion==3):
				ruta.append('r')
				ruta.append('b')	
			ruta.append('f')			
			direccion=2			
			r[1]=r[1]+1
		elif(r[1]-1>-1 and a[r[0]][r[1]-1]==menor):
			#if(matrix[r[0]][r[1]-1]=='H'):
			#	matrix[r[0]][r[1]]='R'
			#	matrix[r[0]][r[1]-1]='R'
			#else:
			matrix[r[0]][r[1]-1]='H'
			if(direccion==1):
				ruta.append('r')

			if(direccion==3):
				ruta.append('l')
				ruta.append('b')
			ruta.append('f')
			direccion=4
			r[1]=r[1]-1
		for i in range(49):
			for j in range(49):
				if(matrix[i][j]=='R' or matrix[i][j]=='O' or matrix[i][j]=='G' or matrix[i][j]=='H' or matrix[i][j]==1):
			        	#temp = temp + str(i)+ ',' + str(j)
					temp = temp + str(matrix[i][j])
				else:
					temp = temp + '*'
			temp = temp + '\n'
		print (temp)
		temp = ''
		#for i in range(49):
        	#	for j in range(49):
		#		temp = temp + str(round(a[i][j]/10000,2))
		#	print temp
		#	temp = ''
		print (a[41][28])
		print (a[42][28])
		print (a[41][29])
		print (a[42][29])
		print (a[41][30])
		print (a[42][30])
		print (a[41][31])
		print (a[42][31])
		print (a[41][32])
		print (a[42][32])
		print (a[40][32])
		print (a[39][32])
		debug=input('d')
	return ruta

def talker():
   
   #rospy.init_node('talker', anonymous=True)
   #rospy.Subscriber('ultrasonic_sensor', Range, callback)
   #opt=raw_input('Effort')
   
   temp=''
   matrix=[]
   ruta=[]
   a=[]
   o=[]
   g=[37,43]
   r=[6,43]
   #g=[6,20]
   #r=[37,20]
   nobs=0
   git = gen_pix_factory(im)
   next(git)
   glim = rgb_to_gray_level(im)
   matrix=binarize(glim)
   print (matrix[41][45])
   #glim.save('Vsevolod_Ivanov_Sichen_bin.bmp')
   for i in range(49):
        for j in range(49):
            if(matrix[i][j]=='O'):
                #print i,j
                o.append(i)
                o.append(j)
                nobs = nobs+1

   for i in range(50):
        s=[]
        for j in range(50):
            s.append(0)
        a.append(s)
   matrix[g[0]][g[1]]='G'
   ruta=camino(a,r,nobs,o,g,matrix)
   for i in matrix:
       for j in i:
           if(j=='R' or j=='O' or j=='G' or j==1):
               temp = temp + str(j)
           else:
               temp = temp + '*'
       print (temp)
       temp = ''
   
   print (ruta)
   #for i in ruta:
   #   callback(i)
   #   time.sleep(2)
   #callback('s')
   #while opt!='c':
	#callback(opt)
	#opt=raw_input('Effort')	
   #rate = rospy.Rate(10) # 10hz
   #while not rospy.is_shutdown()
       #hello_str = "{name: 'motor', effort: 00}"
 #rospy.loginfo(hello_str)
   
       #rate.sleep()
   rospy.spin()
   
if __name__ == '__main__':
  #try:
  talker()
  #except rospy.ROSInterruptException:
  #     pass