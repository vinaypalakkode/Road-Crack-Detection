import python_bow_slic as pbows
import cv2
import time
import numpy as np

inputImage = cv2.imread('../images/street_image.jpg')
bow_slic_creator = pbows.PyBagOfWordsSlic(20, 100, 20)
textonImage = cv2.imread('../images/textons.png',cv2.IMREAD_ANYDEPTH)
inputImage = cv2.resize(inputImage, (0,0), fx=0.5, fy=0.5) 
textonImage = cv2.resize(textonImage, (0,0), fx=0.5, fy=0.5) 
t1 = time.time()
centroids = np.array([]);
superpixelImage, centroids = bow_slic_creator.generate_superpixels_and_centroids(inputImage, 2000)
# superpixelImage
print centroids
# superpixelImage = bow_slic_creator.generate_superpixels(inputImage, 4000)
t2 = time.time()
print t2-t1
overlayImage = bow_slic_creator.overlay_superpixel_boundaries(inputImage, superpixelImage)
cv2.imshow("overlay", overlayImage)
cv2.waitKey(0)
cv2.destroyAllWindows()