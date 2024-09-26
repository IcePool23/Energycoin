// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2021 The Raven Core developers
// Copyright (c) 2023-2024 The Nrgc Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>
#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	CMutableTransaction txNew;
	txNew.nVersion = 1;
	txNew.vin.resize(1);
	txNew.vout.resize(1);
	txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	txNew.vout[0].nValue = genesisReward;
	txNew.vout[0].scriptPubKey = genesisOutputScript;

	CBlock genesis;
	genesis.nTime	= nTime;
	genesis.nBits	= nBits;
	genesis.nNonce   = nNonce;
	genesis.nVersion = nVersion;
	genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
	genesis.hashPrevBlock.SetNull();
	genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
	return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	const char* pszTimestamp = "ENERGY START";
	const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf22d5f") << OP_CHECKSIG;
	return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
	consensus.vDeployments[d].nStartTime = nStartTime;
	consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
	consensus.nSegwitEnabled = false;
}

void CChainParams::TurnOffCSV() {
	consensus.nCSVEnabled = false;
}

void CChainParams::TurnOffBIP34() {
	consensus.nBIP34Enabled = false;
}

void CChainParams::TurnOffBIP65() {
	consensus.nBIP65Enabled = false;
}

void CChainParams::TurnOffBIP66() {
	consensus.nBIP66Enabled = false;
}

bool CChainParams::BIP34() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
	return consensus.nCSVEnabled;
}


/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *	timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
	CMainParams() {
    	strNetworkID = "main";
    	consensus.nSubsidyHalvingInterval = 210000;  // 90 days at 1 min block time
    	consensus.nBIP34Enabled = true;
    	consensus.nBIP65Enabled = true;
    	consensus.nBIP66Enabled = true;
    	consensus.nSegwitEnabled = true;
    	consensus.nCSVEnabled = true;
    	consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    	consensus.kawpowLimit = uint256S("0000000000ffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Estimated starting diff for first 180 kawpow blocks
    	consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
    	consensus.nPowTargetSpacing = 1 * 60;
	consensus.fPowAllowMinDifficultyBlocks = false;
    	consensus.fPowNoRetargeting = false;
    	consensus.nRuleChangeActivationThreshold = 1613; // Approx 80% of 2016
    	consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1711929600; // 2024-04-01 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1735603200; // 2024-12-31 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (RIP2)
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1711929600; // 2024-04-01 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1735603200; // 2024-12-31 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (RIP5)
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1711929600; // 2024-04-01 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1735603200; // 2024-12-31 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714; 
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1711929600; // 2024-04-01 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1735603200; // 2024-12-31 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714; 
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1711929600; // 2024-04-01 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1735603200; // 2024-12-31 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; 
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1711929600; // 2024-04-01 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1735603200; // 2024-12-31 00:00:00
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; 
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;

   		uint32_t nGenesisTime = 1727286590; // 2024-04-27 14:00:00 UTC



arith_uint256 test;
bool fNegative;
bool fOverflow;
test.SetCompact(0x2000ffff, &fNegative, &fOverflow);  // Use a lower difficulty for faster mining
std::cout << "Test threshold (difficulty target): " << test.GetHex() << "\n\n";

int genesisNonce = 0;
uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

// for (int i = 0; i < 40000000; i++) {
//     // Create genesis block with the current nonce
//     genesis = CreateGenesisBlock(nGenesisTime, i, 0x2000ffff, 4, 3000 * COIN);
    
//     // Provide detailed output on the block being created
//     std::cout << "Attempting with Nonce: " << i << std::endl;
//     std::cout << "Genesis Block Time: " << genesis.nTime << std::endl;
//     std::cout << "Genesis Merkle Root: " << genesis.hashMerkleRoot.GetHex() << std::endl;

//     // Hash the genesis block with X16R or X16RV2 (ensure correct hashing algorithm is used)
//     consensus.hashGenesisBlock = genesis.GetX16RHash();  // Adjust if necessary to match the actual algorithm used
//     std::cout << "Current Genesis Hash: " << consensus.hashGenesisBlock.GetHex() << std::endl;

//     // Compare current hash with the best hash found so far
//     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
//     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
//         BestBlockHash = consensus.hashGenesisBlock;
//         std::cout << "New Best Block Hash Found: " << BestBlockHash.GetHex() << std::endl;
//         std::cout << "   Previous Block Hash: " << genesis.hashPrevBlock.GetHex() << std::endl;
//         std::cout << "   Merkle Root: " << genesis.hashMerkleRoot.GetHex() << std::endl;
//     }

//     // Temporary hash to hold the current best hash
//     TempHashHolding = consensus.hashGenesisBlock;

//     // Check if the current hash meets the target difficulty
//     if (UintToArith256(consensus.hashGenesisBlock) < test) {
//         genesisNonce = i;
//         std::cout << "Genesis Block Mined Successfully!" << std::endl;
//         std::cout << "Final Nonce: " << i << std::endl;
//         break;
//     }

//     // Print feedback every 10000 iterations for better tracking
//     if (i % 10000 == 0) {
//         std::cout << "Still working... Current Nonce: " << i << " | Best Hash: " << BestBlockHash.GetHex() << std::endl;
//     }
// }

// std::cout << "\nGenesis Block Found!" << std::endl;
// std::cout << "hashGenesisBlock: " << BestBlockHash.GetHex() << std::endl;
// std::cout << "Genesis Nonce: " << genesisNonce << std::endl;
// std::cout << "Genesis Merkle Root: " << genesis.hashMerkleRoot.GetHex() << std::endl;

// std::cout << "\nMining Statistics:\n";
// int totalHits = 0;
// double totalTime = 0.0;
// for (int x = 0; x < 16; x++) {
//     totalHits += algoHashHits[x];
//     totalTime += algoHashTotal[x];
//     if (algoHashHits[x] > 0) {
//         std::cout << "Hash Algorithm " << x << ": Hits = " << algoHashHits[x] 
//                   << ", Total Time = " << algoHashTotal[x] 
//                   << ", Average Time = " << algoHashTotal[x] / algoHashHits[x] << std::endl;
//     }
// }

// std::cout << "Total Hits: " << totalHits << ", Total Time: " << totalTime 
//           << ", Average Time per Hit: " << (totalHits > 0 ? totalTime / totalHits : 0) << std::endl;

// // Ensure the hash of the previous block is correct (though in genesis block it's null)
// genesis.hashPrevBlock = TempHashHolding;

// return;




 

    	// The best chain should have at least this much work
    	consensus.nMinimumChainWork = uint256S("0x00"); // New blockchain

    	// By default assume that the signatures in ancestors of this block are valid. Block# 0
    	consensus.defaultAssumeValid = uint256S("0x00"); // Genesis block


	pchMessageStart[0] = 0x4e; // 'N'
	pchMessageStart[1] = 0x52; // 'R'
	pchMessageStart[2] = 0x47; // 'G'
	pchMessageStart[3] = 0x43; // 'C'
        nDefaultPort = 9876;
        nPruneAfterHeight = 100000;

	genesis = CreateGenesisBlock(nGenesisTime, 119, 0x2000ffff, 4, 3000 * COIN);

    	consensus.hashGenesisBlock = genesis.GetX16RHash();

    	printf("genesis.GetX16RHash = %s \n", genesis.GetX16RHash().ToString().c_str());
    	printf("Merkle = %s \n", genesis.hashMerkleRoot.ToString().c_str());
    	printf("Nonce = %u \n",  genesis.nNonce);

	assert(consensus.hashGenesisBlock == uint256S("0x0046e5fbb1efd97f16be3d0d6e647d5157212718bf5f9ab3cd3c3e58523a9ff8")); // Mined genesis block hash
	assert(genesis.hashMerkleRoot == uint256S("0x6fd78a1beb36e54d4fe98299e5895b7ef9ab352282350b2ff459e9c04b77e15a")); // Mined Merkle root



    	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,76);  // X and 0x4c
    	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,33);
    	base58Prefixes[SECRET_KEY] = 	std::vector<unsigned char>(1,128);
    	base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
    	base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

    	// Raven BIP44 cointype in mainnet is '0'
    	nExtCoinType = 0;

    	vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

    	fDefaultConsistencyChecks = false;
    	fRequireStandard = true;
    	fMineBlocksOnDemand = false;
    	fMiningRequiresPeers = true;

    	checkpointData = (CCheckpointData) {
        	{
    	{ 0, genesis.GetX16RHash()}
	//{ 0, genesis.GetHash()}
        	}
    	};

    	chainTxData = ChainTxData{
        	nGenesisTime, // * UNIX timestamp of last known number of transactions
        	0,	// * total number of transactions between genesis and that timestamp
                    	//   (the tx=... number in the SetBestChain debug.log lines)
        	0   	// * estimated number of transactions per second after that timestamp
    	};

    	/** NRGC Start **/
    	// Burn Amounts
    	nIssueAssetBurnAmount = 50 * COIN;
    	nReissueAssetBurnAmount = 10 * COIN;
    	nIssueSubAssetBurnAmount = 10 * COIN;
    	nIssueUniqueAssetBurnAmount = 0.5 * COIN;
    	nIssueMsgChannelAssetBurnAmount = 10 * COIN;
    	nIssueQualifierAssetBurnAmount = 100 * COIN;
    	nIssueSubQualifierAssetBurnAmount = 10 * COIN;
    	nIssueRestrictedAssetBurnAmount = 150 * COIN;
    	nAddNullQualifierTagBurnAmount = 0.01 * COIN;

	// 10% of NRGC Rewards for NRGC investment
	nCommunityAutonomousAmount = 10;

    	// Burn Addresses
    	strIssueAssetBurnAddress = "NCissueAssetXXXXXXXXXXXXXXXXXhhZGt";
    	strReissueAssetBurnAddress = "NCReissueAssetXXXXXXXXXXXXXXVEFAWu";
    	strIssueSubAssetBurnAddress = "NCissueSubAssetXXXXXXXXXXXXXWcwhwL";
    	strIssueUniqueAssetBurnAddress = "NCissueUniqueAssetXXXXXXXXXXWEAe58";
    	strIssueMsgChannelAssetBurnAddress = "NCissueMsgChanneLAssetXXXXXXSjHvAY";
    	strIssueQualifierAssetBurnAddress = "NCissueQuaLifierXXXXXXXXXXXXUgEDbC";
    	strIssueSubQualifierAssetBurnAddress = "NCissueSubQuaLifierXXXXXXXXXVTzvv5";
    	strIssueRestrictedAssetBurnAddress = "NCissueRestrictedXXXXXXXXXXXXzJZ1q";
    	strAddNullQualifierTagBurnAddress = "NCaddTagBurnXXXXXXXXXXXXXXXXZQm5ya";

        	//Global Burn Address
    	strGlobalBurnAddress = "NCBurnXXXXXXXXXXXXXXXXXXXXXXWUo9FV";

	// NRGC Fund
    	strCommunityAutonomousAddress = "XuyCzNG3XdibTQvZgVu7ypmeVDBA1kvyev";
    	// DGW Activation
    	nDGWActivationBlock = 1;

    	nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
    	nMinReorganizationPeers = 4;
    	nMinReorganizationAge = 60 * 60 * 12; // 12 hours

    	nAssetActivationHeight = 1; // Asset activated block height
    	nMessagingActivationBlock = 1; // Messaging activated block height
    	nRestrictedActivationBlock = 1; // Restricted activated block height

    	nKAAAWWWPOWActivationTime = nGenesisTime + 1;
    	nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
    	/** NRGC End **/
	}
};

/**
 * Testnet (v7)
 */
class CTestNetParams : public CChainParams {
public:
	CTestNetParams() {
    	strNetworkID = "test";
    	consensus.nSubsidyHalvingInterval = 2100000;  //~ 4 yrs at 1 min block time
    	consensus.nBIP34Enabled = true;
    	consensus.nBIP65Enabled = true;
    	consensus.nBIP66Enabled = true;
    	consensus.nSegwitEnabled = true;
    	consensus.nCSVEnabled = true;
    	consensus.powLimit = uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    	consensus.kawpowLimit = uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Estimated starting diff for first 180 kawpow blocks
    	consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
    	consensus.nPowTargetSpacing = 1 * 60;
    	consensus.fPowAllowMinDifficultyBlocks = false;
    	consensus.fPowNoRetargeting = false;
    	consensus.nRuleChangeActivationThreshold = 1613; // Approx 80% of 2016
    	consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1893452400; // Mon Dec 31 2029 23:00:00 GMT+0000
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 208;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 288;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 500;

    	// The best chain should have at least this much work.
    	consensus.nMinimumChainWork = uint256S("0x00");

    	// By default assume that the signatures in ancestors of this block are valid.
    	consensus.defaultAssumeValid = uint256S("0x00");


    	pchMessageStart[0] = 0x41; // A
    	pchMessageStart[1] = 0x49; // I
    	pchMessageStart[2] = 0x44; // D
    	pchMessageStart[3] = 0x50; // P	 
    	nDefaultPort = 17002;
    	nPruneAfterHeight = 1000;

		uint32_t nGenesisTime = 1714226400; // 2024-04-27 14:00:00 UTC
  	 
    	genesis = CreateGenesisBlock(nGenesisTime, 21553080, 0x1e00ffff, 4, 3000 * COIN);
    	consensus.hashGenesisBlock = genesis.GetX16RHash();


    	//Test MerkleRoot and GenesisBlock
    	assert(consensus.hashGenesisBlock == uint256S("000000181ba07f82878f548c2f3e00f176e1e9deacdccac87b13ae3885ecc3c7"));
    	assert(genesis.hashMerkleRoot == uint256S("5cea53563cff1395d6da77cafeb5ee426ac6be7fe9166a3c0e696c38fa0be698"));

    	vFixedSeeds.clear();
    	vSeeds.clear();

    	vSeeds.emplace_back("seed-testnet-raven.bitactivate.com", false);
    	vSeeds.emplace_back("seed-testnet-raven.ravencoin.com", false);
    	vSeeds.emplace_back("seed-testnet-raven.ravencoin.org", false);

	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,20);  // A
    	base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);  // A
    	base58Prefixes[SECRET_KEY] = 	std::vector<unsigned char>(1,239);
    	base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
    	base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

    	// Nrgc BIP44 cointype in testnet
    	nExtCoinType = 1;

    	vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

    	fDefaultConsistencyChecks = false;
    	fRequireStandard = false;
    	fMineBlocksOnDemand = false;
    	fMiningRequiresPeers = true;

    	checkpointData = (CCheckpointData) {
        	{
                	{0, genesis.GetHash()}
        	}
    	};

    	chainTxData = ChainTxData{
        	// Update as we know more about the contents of the Raven chain
        	// Stats as of 00000023b66f46d74890287a7b1157dd780c7c5fdda2b561eb96684d2b39d62e window size 43200
        	0, // * UNIX timestamp of last known number of transactions
        	0, 	// * total number of transactions between genesis and that timestamp
                    	//   (the tx=... number in the SetBestChain debug.log lines)
        	0.0    	// * estimated number of transactions per second after that timestamp
    	};

    	/** NRGC Start **/
    	// Burn Amounts
    	nIssueAssetBurnAmount = 50 * COIN;
    	nReissueAssetBurnAmount = 10 * COIN;
    	nIssueSubAssetBurnAmount = 10 * COIN;
    	nIssueUniqueAssetBurnAmount = 0.5 * COIN;
    	nIssueMsgChannelAssetBurnAmount = 10 * COIN;
    	nIssueQualifierAssetBurnAmount = 100 * COIN;
    	nIssueSubQualifierAssetBurnAmount = 10 * COIN;
    	nIssueRestrictedAssetBurnAmount = 150 * COIN;
    	nAddNullQualifierTagBurnAmount = 0.01 * COIN;

	// 10% of NRGC Rewards for NRGC investment
	nCommunityAutonomousAmount = 10;

    	// Burn Addresses
    	strIssueAssetBurnAddress = "n1issueAssetXXXXXXXXXXXXXXXXWdnemQ";
    	strReissueAssetBurnAddress = "n1ReissueAssetXXXXXXXXXXXXXXWG9NLd";
    	strIssueSubAssetBurnAddress = "n1issueSubAssetXXXXXXXXXXXXXbNiH6v";
    	strIssueUniqueAssetBurnAddress = "n1issueUniqueAssetXXXXXXXXXXS4695i";
    	strIssueMsgChannelAssetBurnAddress = "n1issueMsgChanneLAssetXXXXXXT2PBdD";
    	strIssueQualifierAssetBurnAddress = "n1issueQuaLifierXXXXXXXXXXXXUysLTj";
    	strIssueSubQualifierAssetBurnAddress = "n1issueSubQuaLifierXXXXXXXXXYffPLh";
    	strIssueRestrictedAssetBurnAddress = "n1issueRestrictedXXXXXXXXXXXXZVT9V";
    	strAddNullQualifierTagBurnAddress = "n1addTagBurnXXXXXXXXXXXXXXXXX5oLMH";

	// Donation Address
    	strCommunityAutonomousAddress = "XuyCzNG3XdibTQvZgVu7ypmeVDBA1kvyev";

    	// Global Burn Address
    	strGlobalBurnAddress = "n1BurnXXXXXXXXXXXXXXXXXXXXXXU1qejP";

    	// DGW Activation
    	nDGWActivationBlock = 1;

    	nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
    	nMinReorganizationPeers = 4;
    	nMinReorganizationAge = 60 * 60 * 12; // 12 hours

    	nAssetActivationHeight = 1; // Asset activated block height
    	nMessagingActivationBlock = 1; // Messaging activated block height
    	nRestrictedActivationBlock = 1; // Restricted activated block height

    	nKAAAWWWPOWActivationTime = nGenesisTime + 1;
    	nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
    	/** NRGC End **/
	}
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
	CRegTestParams() {
    	strNetworkID = "regtest";
    	consensus.nBIP34Enabled = true;
    	consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
    	consensus.nBIP66Enabled = true;
    	consensus.nSegwitEnabled = true;
    	consensus.nCSVEnabled = true;
    	consensus.nSubsidyHalvingInterval = 150;
    	consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    	consensus.kawpowLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    	consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
    	consensus.nPowTargetSpacing = 1 * 60;
    	consensus.fPowAllowMinDifficultyBlocks = true;
    	consensus.fPowNoRetargeting = true;
    	consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
    	consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (RIP5)
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0; // GMT: Sun Mar 3, 2019 5:00:00 PM
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 208;
    	consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 288;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
    	consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 0;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1893452400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 400;
    	consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 500;

    	// The best chain should have at least this much work.
    	consensus.nMinimumChainWork = uint256S("0x00");

    	// By default assume that the signatures in ancestors of this block are valid.
    	consensus.defaultAssumeValid = uint256S("0x00");

    	pchMessageStart[0] = 0x41; // A
    	pchMessageStart[1] = 0x49; // I
    	pchMessageStart[2] = 0x44; // D
    	pchMessageStart[3] = 0x50; // P
    	nDefaultPort = 17003;
    	nPruneAfterHeight = 1000;

   		uint32_t nGenesisTime = 1714226400; // 2024-04-27 14:00:00 UTC


    	genesis = CreateGenesisBlock(nGenesisTime, 1, 0x207fffff, 4, 600 * COIN);
    	consensus.hashGenesisBlock = genesis.GetX16RHash();

    	assert(consensus.hashGenesisBlock == uint256S("00000035b0150cb21b97bbc9b3cce325d623e2debf333925f383e58a57fd6961"));
    	assert(genesis.hashMerkleRoot == uint256S("e5730bfde1b85e96d78d415c5135cf3c789c37d895d8cbacf7e6e9d64c3f00af"));

    	vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
    	vSeeds.clear();  	//!< Regtest mode doesn't have any DNS seeds.

    	fDefaultConsistencyChecks = true;
    	fRequireStandard = false;
    	fMineBlocksOnDemand = true;

    	checkpointData = (CCheckpointData) {
        	{
        	}
    	};

    	chainTxData = ChainTxData{
        	0,
        	0,
        	0
    	};

    	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,76);  // X and 0x4c
    	base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,76);  // X and 0x4c
    	base58Prefixes[SECRET_KEY] = 	std::vector<unsigned char>(1,239);
    	base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
    	base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

    	// Raven BIP44 cointype in regtest
    	nExtCoinType = 1;

    	/** NRGC Start **/
    	// Burn Amounts
    	nIssueAssetBurnAmount = 50 * COIN;
    	nReissueAssetBurnAmount = 10 * COIN;
    	nIssueSubAssetBurnAmount = 10 * COIN;
    	nIssueUniqueAssetBurnAmount = 0.5 * COIN;
    	nIssueMsgChannelAssetBurnAmount = 10 * COIN;
    	nIssueQualifierAssetBurnAmount = 100 * COIN;
    	nIssueSubQualifierAssetBurnAmount = 10 * COIN;
    	nIssueRestrictedAssetBurnAmount = 150 * COIN;
    	nAddNullQualifierTagBurnAmount = 0.01 * COIN;

	// 10% of NRGC Rewards for NRGC investment
	nCommunityAutonomousAmount = 10;

    	// Burn Addresses
    	strIssueAssetBurnAddress = "n1issueAssetXXXXXXXXXXXXXXXXWdnemQ";
    	strReissueAssetBurnAddress = "n1ReissueAssetXXXXXXXXXXXXXXWG9NLd";
    	strIssueSubAssetBurnAddress = "n1issueSubAssetXXXXXXXXXXXXXbNiH6v";
    	strIssueUniqueAssetBurnAddress = "n1issueUniqueAssetXXXXXXXXXXS4695i";
    	strIssueMsgChannelAssetBurnAddress = "n1issueMsgChanneLAssetXXXXXXT2PBdD";
    	strIssueQualifierAssetBurnAddress = "n1issueQuaLifierXXXXXXXXXXXXUysLTj";
    	strIssueSubQualifierAssetBurnAddress = "n1issueSubQuaLifierXXXXXXXXXYffPLh";
    	strIssueRestrictedAssetBurnAddress = "n1issueRestrictedXXXXXXXXXXXXZVT9V";
    	strAddNullQualifierTagBurnAddress = "n1addTagBurnXXXXXXXXXXXXXXXXX5oLMH";

	// Donation Address
    	strCommunityAutonomousAddress = "Axxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    	// Global Burn Address
    	strGlobalBurnAddress = "n1BurnXXXXXXXXXXXXXXXXXXXXXXU1qejP";

    	// DGW Activation
    	nDGWActivationBlock = 200;

    	nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
    	nMinReorganizationPeers = 4;
    	nMinReorganizationAge = 60 * 60 * 12; // 12 hours

    	nAssetActivationHeight = 0; // Asset activated block height
    	nMessagingActivationBlock = 0; // Messaging activated block height
    	nRestrictedActivationBlock = 0; // Restricted activated block height

    	// TODO, we need to figure out what to do with this for regtest. This effects the unit tests
    	// For now we can use a timestamp very far away
    	// If you are looking to test the kawpow hashing function in regtest. You will need to change this number
    	nKAAAWWWPOWActivationTime = 3582830167;
    	nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
    	/** NRGC End **/
	}
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &GetParams() {
	assert(globalChainParams);
	return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
	if (chain == CBaseChainParams::MAIN)
    	return std::unique_ptr<CChainParams>(new CMainParams());
	else if (chain == CBaseChainParams::TESTNET)
    	return std::unique_ptr<CChainParams>(new CTestNetParams());
	else if (chain == CBaseChainParams::REGTEST)
    	return std::unique_ptr<CChainParams>(new CRegTestParams());
	throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network, bool fForceBlockNetwork)
{
	SelectBaseParams(network);
	if (fForceBlockNetwork) {
    	bNetwork.SetNetwork(network);
	}
	globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
	globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}
