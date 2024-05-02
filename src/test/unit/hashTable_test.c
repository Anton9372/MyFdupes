#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../../main/hash_table/hashTable.h"
#include "../../main/hashing/sha256.h"


void printTable(const HashTable* table) {
	for (size_t i = 0; i < table->capacity; i++) {
		HTNode* current = table->table[i];
		printf("Bucket %2d: ", i);
		while (current != NULL) {
			printf("%s --> ", current->value);
			current = current->next;
		}
		printf("\n");
	}
}

bool test1() {
	bool answer = true;
	HashTable* table = HTConstructor(5);

	char* data[] = { "Hello", "World", "Hash", "Table"};
	uint8_t key[4][KEY_LENGTH];

	for (size_t i = 0; i < 4; i++) {
		sha256(data[i], strlen(data[i]), key[i]);
		HTInsert(table, key[i], data[i]);
	}

	for (size_t i = 0; i < 4; i++) {
		char* result = HTGet(table, key[i]);
		if (result == NULL || strcmp(data[i], result) != 0) {
			answer = false;
			break;
		}
	}

	HTDestructor(table);

	return answer;
}

bool test2() {
	bool answer = true;
	HashTable* table = HTConstructor(5);

	char* data[] = { "Hello", "Hello", "Hashing", "Table" };
	uint8_t key[4][KEY_LENGTH];

	for (size_t i = 0; i < 4; i++) {
		sha256(data[i], strlen(data[i]), key[i]);
		HTInsert(table, key[i], data[i]);
	}

	for (size_t i = 0; i < 4; i++) {
		char* result = HTGet(table, key[i]);
		if (result == NULL || strcmp(data[i], result) != 0) {
			answer = false;
			break;
		}
	}

	HTDestructor(table);

	return answer;
}

bool test3() {
	bool answer = true;
	HashTable* table = HTConstructor(5);

	char* data[] = { "Hello", "World", "Hash", "Table" };
	uint8_t key[4][KEY_LENGTH];

	for (size_t i = 0; i < 4; i++) {
		sha256(data[i], strlen(data[i]), key[i]);
		HTInsert(table, key[i], data[i]);
	}

	HTRemove(table, key[2]);
	HTRemove(table, key[3]);

	for (size_t i = 0; i < 2; i++) {
		char* result = HTGet(table, key[i]);
		if (result == NULL || strcmp(data[i], result) != 0) {
			answer = false;
			break;
		}
	}

	HTDestructor(table);

	return answer;
}

bool test4() {
	bool answer = true;
	HashTable* table = HTConstructor(5);

	char* data[] = { "Table", "Hello", "Hello", "Hashing" };
	uint8_t key[4][KEY_LENGTH];

	for (size_t i = 0; i < 4; i++) {
		sha256(data[i], strlen(data[i]), key[i]);
		HTInsert(table, key[i], data[i]);
	}

	HTRemove(table, key[3]);

	for (size_t i = 0; i < 3; i++) {
		char* result = HTGet(table, key[i]);
		if (result == NULL || strcmp(data[i], result) != 0) {
			answer = false;
			break;
		}
	}

	HTRemove(table, key[2]);

	for (size_t i = 0; i < 1; i++) {
		char* result = HTGet(table, key[i]);
		if (result == NULL || strcmp(data[i], result) != 0) {
			answer = false;
			break;
		}
	}

	HTDestructor(table);

	return answer;
}

char* bigData[] = {
    "Table",
    "Hello world",
    "Hello there how are you",
    "Hashing is important for security",
    "Computer science is fascinating",
    "Programming languages vary in syntax",
    "Algorithm complexity analysis is crucial",
    "Data structures organize information",
    "Network protocols facilitate communication",
    "Machine learning enables AI applications",
    "Artificial intelligence mimics human behavior",
    "Robotics automates repetitive tasks",
    "Automation streamlines production processes",
    "Virtual reality creates immersive experiences",
    "Augmented reality overlays digital content",
    "Blockchain ensures data integrity",
    "Cryptocurrency transactions are decentralized",
    "Computer science is fascinating",
    "Programming languages vary in syntax",
    "Bitcoin is a popular digital currency",
    "Ethereum supports smart contracts",
    "Smart contracts execute automatically",
    "Decentralized finance revolutionizes banking",
    "DeFi platforms offer high yields",
    "NFTs represent unique digital assets",
    "Tokenization simplifies asset management",
    "Exchange platforms facilitate trading",
    "Internet connects the world",
    "Things are becoming interconnected",
    "Cybersecurity protects digital assets",
    "Privacy concerns drive encryption adoption",
    "Authentication verifies user identities",
    "Authorization grants access rights",
    "Firewalls filter network traffic",
    "Intrusion detection systems monitor threats",
    "Prevention mechanisms mitigate risks",
    "Vulnerability assessments identify weaknesses",
    "Exploits leverage system flaws",
    "Patches fix software vulnerabilities",
    "Software development requires coding skills",
    "Hardware components are physical",
    "Operating systems manage resources",
    "Windows is a widely used OS",
    "Linux is open-source",
    "Unix is the foundation for many OS",
    "macOS is known for its user interface",
    "iOS powers Apple mobile devices",
    "Android dominates the smartphone market",
    "Mobile applications enhance productivity",
    "Web development spans frontend and backend",
    "Responsive design adapts to screen sizes",
    "UI/UX design focuses on user experience",
    "Database management is crucial for data storage",
    "SQL enables relational database querying",
    "NoSQL databases offer flexible schemas",
    "MySQL is popular for web applications",
    "SQLite is lightweight and embedded",
    "PostgreSQL is known for scalability",
    "MongoDB is a document-oriented database",
    "Redis is used for caching",
    "Caching improves application performance",
    "Performance optimization boosts efficiency",
    "Testing ensures software quality",
    "Unit tests verify individual components",
    "Integration tests check interactions",
    "System tests validate overall behavior",
    "Acceptance tests confirm user requirements",
    "Regression tests prevent code regressions",
    "Agile methodologies prioritize flexibility",
    "Scrum emphasizes iterative development",
    "Kanban visualizes workflow",
    "Waterfall follows a sequential approach",
     "NFTs represent unique digital assets",
    "Tokenization simplifies asset management",
    "Exchange platforms facilitate trading",
    "Internet connects the world",
    "Things are becoming interconnected",
    "Cybersecurity protects digital assets",
    "Privacy concerns drive encryption adoption",
    "Authentication verifies user identities",
    "Authorization grants access rights",
    "Firewalls filter network traffic",
    "DevOps bridges development and operations",
    "Continuous integration ensures code quality",
    "Deployment automates software delivery",
    "Delivery pipelines streamline releases",
    "Version control tracks code changes",
    "Git is a popular version control system",
    "GitHub hosts Git repositories",
    "Bitbucket offers Git repository management",
    "Repositories store project code",
    "Branches isolate code changes",
    "Merges combine code branches",
    "Conflicts arise during code merging",
    "Resolution reconciles conflicting changes",
    "Documentation explains code functionality",
    "Comments provide inline explanations",
    "Readme files offer project overviews",
    "Licenses dictate software usage rights",
    "Open-source software encourages collaboration",
    "Commercial software is proprietary",
    "Freeware is free to use",
    "Shareware offers limited trial periods",
    "Proprietary software restricts source code access",
    "Public licenses allow widespread usage",
    "Private licenses limit usage rights",
    "Cloud computing provides on-demand resources",
    "AWS offers scalable cloud services",
    "Amazon Web Services dominates the market",
    "Azure is Microsoft's cloud platform",
    "Google Cloud Platform competes aggressively",
    "GCP provides infrastructure and services",
    "Infrastructure as a Service offers virtualized resources",
    "Platform as a Service simplifies application deployment",
    "Function as a Service enables serverless computing",
    "Lambda runs code in response to events",
    "S3 provides scalable object storage",
    "EC2 offers resizable compute capacity",
    "RDS manages relational databases",
    "Licenses dictate software usage rights",
    "Open-source software encourages collaboration",
    "Commercial software is proprietary",
    "Freeware is free to use",
    "Route 53 is a DNS web service",
    "IAM controls access to AWS resources",
    "VPC provides isolated network environments",
    "Subnets divide IP networks",
    "Gateway connects different network protocols",
    "Load balancers distribute incoming traffic",
    "Auto scaling adjusts resource allocation",
    "Elastic Beanstalk simplifies application deployment",
    "Lambda enables serverless application hosting",
    "Serverless architecture abstracts infrastructure management",
    "Containers encapsulate application dependencies",
    "Docker facilitates containerization",
    "Kubernetes orchestrates container deployments",
    "Pods group containers for deployment",
    "Volumes provide persistent storage",
    "Networking connects distributed systems",
    "Security ensures data protection",
    "Orchestration automates infrastructure management",
    "Microservices architecture decomposes applications",
    "Monolithic architecture consolidates functionality",
    "RESTful APIs enable communication between systems",
    "GraphQL simplifies API querying",
    "SOAP is a protocol for exchanging structured information",
    "RPC facilitates remote procedure calls",
    "Client-server architecture separates concerns",
    "Peer-to-peer networks distribute workloads",
    "Communication protocols define data exchange rules",
    "Sockets enable network communication",
    "TCP ensures reliable data delivery",
    "UDP supports connectionless communication",
    "HTTP transfers hypertext documents",
    "HTTPS secures HTTP connections",
    "FTP transfers files over networks",
    "SMTP sends email messages",
    "POP3 retrieves email messages",
    "IMAP manages email on servers",
    "SSH provides secure remote access",
    "SSL secures data transmission",
    "TLS encrypts data for secure communication",
    "Cryptography protects data integrity",
    "Symmetric encryption uses shared keys",
    "Asymmetric encryption uses key pairs",
    "Public keys encrypt data for specific recipients",
    "Private keys decrypt data for authorized users",
    "Key exchange protocols ensure secure communication",
    "Encryption algorithms transform plaintext into ciphertext",
    "Decryption algorithms reverse encryption",
    "Hash functions generate fixed-size digests",
    "MD5 is a cryptographic hash function",
    "SHA-1 produces 160-bit hash values",
    "UDP supports connectionless communication",
    "HTTP transfers hypertext documents",
    "HTTPS secures HTTP connections",
    "SHA-256 generates 256-bit hash values",
    "Blockchain technology enables distributed consensus",
    "Consensus algorithms validate transaction blocks",
    "Blockchain technology enables distributed consensus",
    "Proof of Work requires computational effort",
    "Proof of Stake validates transactions based on ownership",
    "Mining secures blockchain networks",
    "Blockchain technology enables distributed consensus",
    "Wallets store cryptographic keys",
    "Blockchain technology enables distributed consensus",
    "Addresses identify wallet owners",
    "Transactions transfer digital assets",
    "Blockchain technology enables distributed consensus",
    "Smart contracts automate contract execution",
    "Solidity is a programming language for smart contracts",
    "EVM executes smart contract bytecode",
    "Gas measures computational cost",
    "ERC-20 defines fungible token standards",
    "ERC-721 specifies non-fungible token standards",
    "DeFi platforms offer decentralized exchanges",
    "DEX facilitates peer-to-peer trading",
    "Liquidity pools provide trading liquidity",
    "Yield farming maximizes returns",
    "NFTs represent unique digital assets",
    "Non-fungible tokens have distinct metadata",
    "ERC-721 defines NFT token standards",
    "IPFS stores and retrieves NFT metadata",
    "InterPlanetary File System enables decentralized storage",
    "Decentralization ensures network resilience",
    "Centralization concentrates control in few hands",
    "Trust is essential for centralized systems",
    "Trustless systems operate without central authority",
    "Permission systems restrict access to authorized users",
    "Public keys authenticate user identities",
    "Private keys authorize access to resources",
    "Biometric authentication verifies physical characteristics",
    "Multifactor authentication combines different authentication methods",
    "Tokens provide temporary access credentials",
    "OAuth delegates user authentication to third parties",
    "OpenID enables single sign-on authentication",
    "SAML exchanges authentication and authorization data",
    "RBAC defines role-based access control policies",
    "SSO enables users to access multiple systems with one login",
    "Password managers securely store login credentials",
    "Password hashing protects passwords from plaintext exposure",
    "Salting prevents rainbow table attacks",
    "Rainbow tables map hashed passwords to plaintext equivalents",
    "Brute force attacks try all possible combinations",
    "Dictionary attacks use word lists to guess passwords",
    "Social engineering exploits human psychology",
    "Phishing uses deceptive emails to steal information",
    "Spoofing impersonates legitimate entities",
    "Man-in-the-middle attacks intercept communication",
    "Trojans disguise malware as legitimate software",
    "Viruses replicate and spread within systems",
    "Biometric authentication verifies physical characteristics",
    "Multifactor authentication combines different authentication methods",
    "Tokens provide temporary access credentials",
    "OAuth delegates user authentication to third parties",
    "OpenID enables single sign-on authentication",
    "SAML exchanges authentication and authorization data",
    "RBAC defines role-based access control policies",
    "Malware compromises system security",
    "Ransomware encrypts files for ransom",
    "Worms self-propagate across networks",
    "Spyware monitors user activities",
    "Adware displays unwanted advertisements",
    "Firewalls filter network traffic",
    "Antivirus software detects and removes malware",
    "Intrusion detection systems monitor for suspicious activities",
    "Prevention mechanisms mitigate security risks",
    "Backup solutions protect against data loss",
    "Restore procedures recover lost data",
    "Disaster recovery plans ensure business continuity",
    "Business continuity plans minimize downtime",
    "Incident response procedures address security breaches",
    "Forensic analysis investigates security incidents",
    "Audit trails record system activities",
    "Compliance ensures adherence to regulations",
    "Regulations mandate data protection standards",
    "GDPR protects personal data privacy",
    "HIPAA safeguards healthcare information",
    "PCI DSS secures credit card transactions",
    "Prevention mechanisms mitigate security risks",
    "Backup solutions protect against data loss",
    "SOX ensures financial transparency",
    "FERPA protects student educational records",
    "COPPA regulates online data collection from children",
    "CCPA grants California residents data privacy rights",
    "Breach notifications inform affected parties",
    "Data protection policies safeguard sensitive information",
    "Privacy policies outline data usage practices",
    "Terms of service define user rights and responsibilities",
    "License agreements dictate software usage terms",
    "Intellectual property rights protect creative works",
    "Trademarks identify and protect brand assets",
    "Copyrights safeguard original works of authorship",
    "Patents grant exclusive rights to inventions",
    "Trade secrets protect confidential business information",
    "Litigation resolves legal disputes",
    "Legal cases involve litigation proceedings",
    "Laws establish legal rights and obligations",
    "Judges preside over court proceedings",
    "Courts adjudicate legal disputes",
    "Trials determine factual and legal issues",
    "Arbitration resolves disputes outside of court",
    "License agreements dictate software usage terms",
    "Intellectual property rights protect creative works",
    "Trademarks identify and protect brand assets",
    "Mediation facilitates voluntary dispute resolution",
    "Settlement agreements resolve legal claims",
    "Appeals challenge trial court decisions",
    "Verdicts determine guilt or innocence",
    "Plaintiffs initiate legal proceedings",
    "Defendants respond to legal claims",
    "Prosecutors represent the state in criminal cases",
    "Defense attorneys represent defendants",
    "Lawyers advocate for clients' legal interests",
    "Attorneys provide legal counsel and representation",
    "License agreements dictate software usage terms",
    "Intellectual property rights protect creative works",
    "Trademarks identify and protect brand assets",
    "Solicitors handle legal matters in some jurisdictions",
    "Barristers advocate in court proceedings",
    "Jurisdiction determines the legal authority of courts",
    "Forums provide venues for legal proceedings",
    "Venues host court hearings and trials",
    "Discovery processes exchange legal information",
    "Evidence supports legal arguments",
    "Witnesses testify about relevant facts",
    "Testimony provides sworn statements",
    "Depositions gather pre-trial witness testimony",
    "Subpoenas compel witness testimony or evidence",
    "Summons notify parties of legal actions",
    "Warrants authorize searches or arrests",
    "Affidavits provide sworn statements of fact",
    "Perjury constitutes lying under oath",
    "Contempt of court involves disobedience to legal orders",
    "Judgments resolve legal disputes",
    "Damages compensate for legal injuries",
    "Injunctions prohibit certain actions",
    "Restitution restores harmed parties to their original condition",
    "Compensation provides monetary remedies",
    "Punitive damages punish wrongful conduct",
    "General damages compensate for non-economic losses",
    "Special damages reimburse specific expenses",
    "Actual damages compensate for actual losses",
    "Nominal damages acknowledge legal wrongs",
    "Liquidated damages pre-determine compensation amounts",
    "Exemplary damages deter future misconduct",
    "Consequential damages compensate for indirect losses",
    "Torts involve civil wrongs",
    "Negligence breaches a duty of care",
    "Strict liability imposes liability without fault",
    "Product liability concerns defective products",
    "Premises liability involves property hazards",
    "Defamation damages reputation",
    "Libel constitutes written defamation",
    "Slander involves spoken defamation",
    "Fraud entails intentional deception",
    "Misrepresentation involves false statements",
    "Embezzlement misappropriates funds",
    "Forgery falsifies documents or signatures",
    "Counterfeit products imitate genuine items",
    "False advertising misleads consumers",
    "Antitrust laws regulate competition",
    "Negligence breaches a duty of care",
    "Strict liability imposes liability without fault",
    "Product liability concerns defective products",
    "Premises liability involves property hazards",
    "Monopolies control market share",
    "Mergers combine companies",
    "Acquisitions buy out companies",
    "Acquisitions buy out companies",
    "Joint ventures pool resources for mutual benefit",
    "Partnerships share profits and liabilities",
    "Corporations are legal entities",
    "LLCs offer limited liability protection",
    "Acquisitions buy out companies",
    "Acquisitions buy out companies",
    "Acquisitions buy out companies",
    "Acquisitions buy out companies",
    "Acquisitions buy out companies",
    "Limited liability companies protect personal assets",
    "Sole proprietorships are owned by individuals",
    "Nonprofit organizations serve public interests",
    "501(c)(3) organizations qualify for tax exemption",
    "Tax exemptions reduce financial burdens",
    "501(c)(4) organizations engage in political activities",
    "Political action committees advocate for political causes",
    "Lobbying influences government policies",
    "Donations support charitable causes",
    "Contributions fund political campaigns",
    "Campaign finance regulations govern political spending",
    "Elections determine political leadership",
    "Primary elections select party candidates",
    "General elections decide officeholders",
    "Presidential elections choose national leaders",
    "Congressional elections elect representatives",
    "Senate elections determine senators",
    "House elections select representatives",
    "Legislation creates laws",
    "Bills propose legislative actions",
    "Statutes codify legal rules",
    "Regulations implement statutory mandates",
    "Executive orders direct administrative actions",
    "Ordinances regulate local matters",
    "Resolutions express official opinions",
    "Constitutions establish fundamental laws",
    "Amendments modify constitutional provisions",
    "Articles delineate governmental powers",
    "Federal laws apply nationwide",
    "State laws govern within state boundaries",
    "Local ordinances regulate municipal affairs",
    "Jurisdiction determines legal authority",
    "Venues host legal proceedings",
    "Trials resolve factual disputes",
    "Courts administer justice",
    "Appellate courts review lower court decisions",
    "Supreme courts have final appellate jurisdiction",
    "District courts handle federal cases",
    "Circuit courts hear appeals from district courts",
    "Bankruptcy courts oversee bankruptcy proceedings",
    "Civil courts resolve non-criminal disputes",
    "Criminal courts adjudicate criminal matters",
    "Family courts handle domestic issues",
    "Juvenile courts address youth offenses",
    "Probate courts oversee wills and estates",
    "Traffic courts handle vehicle-related violations",
    "Small claims courts resolve minor disputes",
    "Alternative dispute resolution methods offer non-litigious options",
    "ADR resolves conflicts outside of traditional litigation",
    "Mediation facilitates voluntary settlement agreements",
    "Arbitration renders binding decisions",
    "Negotiation seeks mutually acceptable solutions",
    "Collaboration fosters joint problem-solving",
    "Facilitation guides group discussions",
    "Conciliation mediates between conflicting parties",
    "Neutral third-party intervenes in disputes",
    "Neutral facilitator promotes dialogue",
    "Mediator assists in reaching agreements",
    "Arbitrator issues binding decisions",
    "Negotiator represents parties' interests",
    "Conflict resolution techniques manage disputes",
    "Restorative justice focuses on healing",
    "Human rights protect fundamental freedoms",
    "Equality ensures fair treatment",
    "Equity promotes justice",
    "Freedom empowers individuals",
    "Democracy facilitates popular governance",
    "Liberty guarantees individual rights",
    "Authority establishes governance structures",
    "Government provides public services",
    "Sovereignty asserts national independence",
    "Legitimacy ensures government acceptance",
    "Power influences political decisions",
    "Monarchy is ruled by a monarch",
    "Dictatorship is governed by a dictator",
    "Autocracy concentrates power in one individual",
    "Oligarchy is controlled by a small group",
    "Aristocracy is ruled by nobility",
    "Government provides public services",
    "Sovereignty asserts national independence",
    "Legitimacy ensures government acceptance",
    "Theocracy is governed by religious leaders",
    "Democracy is governed by the people",
    "Republic is a representative democracy",
    "Constitutional governments abide by constitutions",
    "Parliamentary systems have legislative supremacy",
    "Federal governments have divided powers",
    "Unitary governments have centralized authority",
    "Confederal governments delegate authority to states",
    "Presidential systems separate executive and legislative powers",
    "Prime ministers lead parliamentary governments",
    "Chancellors oversee parliamentary administrations",
    "Legislatures create laws",
    "Congresses represent legislative bodies",
    "Parliaments enact laws and oversee governments",
    "Senates represent upper legislative chambers",
    "Government provides public services",
    "Sovereignty asserts national independence",
    "Legitimacy ensures government acceptance",
    "Houses represent lower legislative chambers",
    "Representatives serve constituencies",
    "Executives implement laws and policies",
    "Presidents lead executive branches",
    "Governors oversee state administrations",
    "Mayors govern municipalities",
    "Prime ministers head parliamentary governments",
    "Chancellors lead parliamentary administrations",
    "Monarchs symbolize national unity",
    "Dictators wield absolute power",
    "Autocrats govern without constraints",
    "Oligarchs influence political decisions",
    "Aristocrats embody inherited privilege",
    "Theocrats justify rule through divine authority",
    "Judiciaries interpret and apply laws",
    "Judges preside over legal proceedings",
    "Government provides public services",
    "Sovereignty asserts national independence",
    "Legitimacy ensures government acceptance",
    "Justices administer justice impartially",
    "Courts adjudicate legal disputes fairly",
    "Lawyers advocate for clients' legal interests",
    "Attorneys provide legal representation",
    "Prosecutors pursue criminal charges",
    "Defense counsels protect defendants' rights",
    "Barristers argue cases in court",
    "Solicitors handle legal matters",
    "Advocates champion causes",
    "Juries assess evidence and render verdicts",
    "Trials determine guilt or innocence",
    "Grand juries consider indictments",
    "Petit juries hear trial cases",
    "Lawsuits resolve legal claims",
    "Complaints initiate legal actions",
    "Petitions request legal relief",
    "Summons notify defendants of legal proceedings",
    "Pleadings present legal arguments",
    "Discovery processes exchange information",
    "Depositions gather witness testimony",
    "Interrogatories solicit written responses",
    "Motions request court rulings",
    "Briefs argue legal positions",
    "Trials examine evidence and testimony",
    "Appeals challenge trial court decisions",
    "Verdicts determine legal outcomes",
    "Judgments enforce legal rights",
    "Sentences impose criminal punishments",
    "Acquittals absolve defendants of guilt",
    "Government provides public services",
    "Sovereignty asserts national independence",
    "Legitimacy ensures government acceptance",
    "Convictions establish criminal liability",
    "Plea bargains reduce criminal charges",
    "Probation sentences suspend incarceration",
    "Parole releases prisoners under supervision",
    "Appeals challenge legal decisions",
    "Resentencing revisits prior sentences",
    "Reversals overturn legal rulings",
    "Remands return cases for further consideration",
    "Sentencing guidelines inform judicial decisions",
    "Corrections facilities incarcerate offenders",
    "Prisons confine convicted criminals",
    "Jails detain individuals awaiting trial",
    "Penitentiaries rehabilitate and punish offenders",
    "Correctional institutions offer inmate programs",
    "Detention centers hold individuals in custody",
    "Rehabilitation programs reform offenders",
    "Parole programs reintegrate ex-offenders",
    "Probation services supervise released offenders",
    "Recidivism rates measure reoffending tendencies",
    "Reentry programs support returning citizens",
    "Reintegration services help ex-offenders reintegrate",
    "Restoration initiatives repair harm caused by crime",
    "Resocialization efforts promote societal reintegration",
    "Reform initiatives seek systemic improvements",
    "Education programs teach vocational skills",
    "Employment opportunities facilitate reintegration",
    "Housing assistance provides stable living arrangements",
    "Treatment programs address underlying issues",
    "Support services aid in reintegration",
    "Government provides public services",
    "Sovereignty asserts national independence",
    "Legitimacy ensures government acceptance",
    "Service organizations offer community support",
    "Programs assist with reentry challenges",
    "Community integration fosters societal acceptance",
    "Transition services ease reintegration challenges",
    "Reentry assistance programs provide support",
    "Counseling services offer emotional support",
    "Therapy sessions address underlying issues",
    "Training programs develop vocational skills",
    "Skill development initiatives enhance employability",
    "Vocational training programs teach job skills",
    "Occupational training programs prepare for specific careers",
    "Educational opportunities promote personal growth",
    "Recreational activities foster leisure interests",
    "Medical services provide healthcare support",
    "Mental health services address psychological needs",
    "Substance abuse programs offer addiction treatment",
    "Addiction recovery programs support sobriety",
    "Dual diagnosis programs address co-occurring disorders",
    "Co-occurring disorder treatment integrates care",
    "Therapeutic interventions promote recovery",
    "Counseling sessions address underlying issues",
    "Medication-assisted treatment supports recovery efforts",
    "MAT combines medication with counseling"
};

bool test5() {
	bool answer = true;
	HashTable* table = HTConstructor(193);

    size_t dataSize = sizeof(bigData) / sizeof(bigData[0]);

    uint8_t** key = (uint8_t**)malloc(dataSize * sizeof(uint8_t*));
    for (size_t i = 0; i < dataSize; i++) {
        key[i] = (uint8_t*)malloc(KEY_LENGTH * sizeof(uint8_t));
    }

	for (size_t i = 0; i < dataSize; i++) {
		sha256(bigData[i], strlen(bigData[i]), key[i]);
		HTInsert(table, key[i], bigData[i]);
	}

	for (size_t i = 0; i < dataSize; i++) {
		char* result = HTGet(table, key[i]);
		if (result == NULL || strcmp(bigData[i], result) != 0) {
			answer = false;
			break;
		}
	}

    printTable(table);

	HTDestructor(table);

	return answer;
}

int main() {

	printf("Test 1: %d\n", test1());
	printf("Test 2: %d\n", test2());
	printf("Test 3: %d\n", test3());
	printf("Test 4: %d\n", test4());
    printf("Test 5: %d\n", test5());

	return 0;
}