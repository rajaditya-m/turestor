#!/usr/bin/env python
# -*- coding: utf-8 -*-
import struct
import os 
import sys 
import subprocess

if __name__ == '__main__' :
    if len(sys.argv) <= 2 or len(sys.argv) > 4 :
        print "Usage: %s exe_name [min_pose_id] max_pose_id " % sys.argv[0]
        sys.exit(0)

    exe_name = sys.argv[1]
    min_pose_id = 0
    max_pose_id = -1 
    if len(sys.argv) == 4 :
        min_pose_id = int(sys.argv[2])
        max_pose_id = int(sys.argv[3])
    else :
	    max_pose_id = int(sys.argv[2])
    print("Generate poses from %d to %d with %s" % (min_pose_id, max_pose_id, exe_name))
    if min_pose_id > max_pose_id :
        print "max pose id is greater than min pose id"
        sys.exit(0);

    pose_num = 0
    for pose_id in range(min_pose_id, max_pose_id + 1) :
        output_file_name = "%d.bin" % pose_id
        # --total_simulation_time 0.4
        command = './%s --simulate 1 --output_file "%s" > log.txt' % (exe_name, output_file_name)
        status = subprocess.call(command, shell = True)
        if os.path.exists(output_file_name):
            pose_num = pose_num + 1
            print "finish pose %d" % pose_id
        else :
            print "pose %d failed" % pose_id
    
    output_file_name = "poses.ar"
    print "Successfully generated %d poses" % pose_num

    pose_file = open(output_file_name, "wb")
    # unsigned long long == size_t, little endian
    pose_file.write(struct.pack("<Q", pose_num))
    for pose_id in range(min_pose_id, max_pose_id + 1) :
#        status = subprocess.call("cat %d.bin >> %s" % (pose_id, output_file_name), shell = True)
        data = open("%d.bin" % pose_id, "rb").read();
        pose_file.write(data)
    pose_file.close()
    print "All poses are written to %s" % output_file_name

