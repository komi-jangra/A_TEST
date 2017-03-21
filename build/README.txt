BSC RB-CS4.0 Build Instructions:
================================
Pre-requisite:
	This BSC build depends on 
		BPM - Binaries and Header files
		DSP - Binaries and Interfaces
	>> Make sure the two dependencies are taken care before starting

	* BPM/Inc header files are linked through tags from BPM repo
	* rest of the deps are got through the build/get* scripts
Pre-Build:
	cd build
	./get_bpm_commonlibs.sh
	./get_bpm_binaries.sh
	./get_dsp_binaries.sh
	./get_dsp_interfaces.sh	

Build:

	* goto Source/Csapp/Util/

	Edit the make.opt in the above dir

export PLATFORM   :=Target
export SYS        :=M2C
export BPM_ENABLE :=1
export BASE       :=4
export MAJOR      :=0
export MINOR      :=1
export LOCATION   :=Vnl  #Aricent VNL

and change accordingly

* cd Tools/Bsc_build
* nohup make all > BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE.log 2>&1 &
* tail the log by tail -f (the build will be completed in 20-30mins)for each

check for errors by 
grep "Error 1" BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE.log

Post-Build:

	For full Install
		make pre-install | tee pre-install.log 2>&1 
		make install | tee full_install.log 2>&1

		(for EIC & RMON the BPM Team given the fllwng steps)
		goto the generated Bsc-install/Target
		untar the pp.tar and delete pp.tar
		cd pp/
		mkdir -p systemRepos/eic/active
		 svn co
http://10.100.211.65/system/pfs/PFS/branches/DEV-EIC/products/eic/images
		cp -rpf /BSC_COMMON/* images/.
		cd images
		run the following!
		./makeEICRepos.sh

		you will get an sr.x.y.z folder
		move this folder to the systemRepos/eic/active
		move out of the images and delete the images
		come out at the Bsc-install/Target level
		and re-tar the pp
		tar -cvf pp.tar pp
		and then remove the pp dir
		then proceed with the full install process
			
		


	For s/w upgrade:
		export TAR_FOR_UPGRADE=1
		Go to Tools/Bsc_build
		make install
		Go inside Bsc-install /Target/sr.3.0.9
Example:
/home/hindustan.bscbuild/build_area/BSC_3.0.9_BUILD3/M1/BSCCS2-Development/Bsc-install/Target/sr.3.0.9
	Cpcsc & PPcsc files are present inside sr.3.0.9
	Remove testStubs from CPcsc & PPcsc
		rm -rf CPcsc/testStubs
		rm -rf PPcsc/testStubs
	Go inside CPcsc  
	Remove Scripts_N_Packages from config-3.0.9.
	rm -rf CPcsc/config-3.0.9/Scripts_N_Packages
	Checkout BPM at the top 
	svn export
http://10.100.211.65/system/mwd/BPM/tags/MWD_GREENBOX_0.19 BPM

	Go inside Bsc-install 
		export  BSC_CS3=1


	 Run Upgrade command to generate the upgrade.
		make upgrade

Check errors: The output must say "Target generation done"


Post-Build:

	create the BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE build_version dir in
		staging_area/current
		release_area/current
	and also in the SVN repo

	http://10.100.211.65/node/bsc/BSC-STAGINGAREA/current/BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE

	http://10.100.211.65/node/bsc/BSC-RELEASEAREA/current/BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE
	BUILD ROOT is the
BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE/M2C/BSCCS2-Development (or where the
build area)
	Staging Area:
		copy the $BUILD_ROOT/Bin dir to
staging_area/current/BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE

	tar the Bin dir as
	tar -cvzf BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE.tar.gz Bin

	upload to SVN repo

	Release Area:

	(Full - Install)
	copy the $BUILD_ROOT/Bsc-install to
release_area/current/BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE
	for full install (you need to do this step before the s/w upgrade)
	tar -cvzf BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE_FI.tar.gz Bsc-install

	(S/W - Upgrade)
	copy the $BUILD_ROOT/Bsc-install to
release_area/current/BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE
	for sw upgrade you need to do this step after the full install)
	tar -cvzf BSC_4.0.5_GB_BUILD8_RELEASE_CANDIDATE_SU.tar.gz Bsc-install

IMPORTANT:
Inform the Users that the Staging Area and Release Area are uploaded

End :)
