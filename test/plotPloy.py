import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection
import argparse
import numpy as np



def main():
    # Construct argument parser
    #------------------------------------------------------
    ap = argparse.ArgumentParser()
    ap.add_argument('vertices', type=str,
            help='The vertices')
    ap.add_argument('connectivity', type=str,
            help='The triangle connectivity')
    ap.add_argument('-e','--export', type=str,
            help='Name of PNG for export.',
            default=None)

    args = vars(ap.parse_args())

    vertices = np.loadtxt(args['vertices']).astype('int')
    connectivity = np.loadtxt(args['connectivity']).astype('int')

    patch_args =  {'edgecolor'  : 'k',
                   'linewidths' : 1.0,
                   'facecolors' : '',
                   'joinstyle'  : 'round',
                   'capstyle'   : 'round',
                   'alpha'      : 1.0 }


    fig, ax = plt.subplots(1,1,figsize=(7,7))


    # Plot triangulation
    tri_patches = []
    for tri in connectivity:
        poly = Polygon([(vertices[node][0], vertices[node][1]) for node in tri])
        tri_patches.append(poly)

    patch_col = PatchCollection(tri_patches, **patch_args)
    ax.add_collection(patch_col)

    # Plot polygon
    #poly = Polygon(vertices)
    #patch_col = PatchCollection([poly], edgecolor='k', facecolors='', linewidth=2.0)
    #ax.add_collection(patch_col)

    # Plot vertices
    ax.scatter(vertices[:,0], vertices[:,1], c='k', s=35)

    # Axis limits
    dx = vertices[:,0].max() - vertices[:,0].min()
    dy = vertices[:,1].max() - vertices[:,1].min()

    ax.set_xlim([vertices[:,0].min()-0.1*dx, vertices[:,0].max()+0.1*dx])
    ax.set_ylim([vertices[:,1].min()-0.1*dy, vertices[:,1].max()+0.1*dy])

    # Export image
    if args['export'] is not None:
        fig.savefig(args['export'])
    else:
        plt.show()






if __name__ == '__main__': main()
