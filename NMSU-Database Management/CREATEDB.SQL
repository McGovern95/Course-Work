create table player
   (playerid      integer,
    loginid       varchar(16),
    name           varchar(64) NOT NULL,
    password       varchar(8),
    birthday       date,
    address        varchar(128),
    email          varchar(32),
    phonenumber    char(10),
    playpos        varchar(16)
    check (playpos in ('point guard', 'shooting guard', 'small forward', 'power forward', 'center')), 
    primary key (playerid)
   );
   
   
create table manager
	(managerid	    integer,
     loginid		varchar(16) NOT NULL,
     name			varchar(64) NOT NULL,
     password		varchar(8),
     birthday		date,
     address        varchar(128),
     email          varchar(32),
     phonenumber    char(10),
     primary key (managerid)
  );
  
create table staff
	 (staffid		integer,
	  name			varchar(64) NOT NULL,
      birthday		date,
      address		varchar(128),
      email			varchar(32),
      phonenumber	char(10),
      title 		varchar(16) NOT NULL,
      primary key (staffid)
  );
  
create table managercertificate
	 (managerID		integer,
      certificateid int,
      certificate   BLOB,
      primary key (managerid, certificateid),
	 foreign key (managerID) references manager(managerid)
  );

create table stats
	  (playerid		integer,
	   year			char(4),
	   totalpoints  integer check (TotalPoints >= 0),
       aspg		integer check (aspg >= 0),
       primary key (playerid, year),
       foreign key (playerid) references player(playerid)
  );
  
create table training
       (trainingname varchar(16),
        instruction	 varchar(256) NOT NULL,
        timeperiodinhour integer NOT NULL,
        primary key (trainingname)
   );
   
create table assigntraining
	    (playerid 	 integer,
         managerid   integer,
         trainingname varchar(16),
         primary key (playerid, managerid, trainingname),
         foreign key (playerid) references player(playerid),
         foreign key (managerid) references manager(managerid),
         foreign key (trainingname) references training(trainingname)
    );

create table game
		 (gameid	  integer,
          date		  date NOT NULL,
          result 	  varchar(16) NOT NULL
          check (result in ('Win', 'Lose', 'Tie')), 
          playingvenue varchar(256) NOT NULL,
          opponentteam varchar(32) NOT NULL,
          primary key (gameid)
	);
    
create table play
          (playerid   integer,
           gameid  integer,
           primary key (playerid,gameid),
           foreign key (playerid) references player(playerid),
           foreign key (gameid) references game(gameid)
	);
